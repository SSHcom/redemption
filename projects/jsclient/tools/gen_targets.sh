#!/bin/bash

set -e

cd "$(dirname "$0")/../../.."
d=projects/jsclient

disable_sources=''
for f in \
    src/mod/rdp/channels/*.hpp \
    src/mod/rdp/rdp_metrics.hpp \
    src/mod/metrics.hpp \
    src/RAIL/client_execute.hpp \
    src/core/RDP/capabilities/rail.hpp \
    src/core/RDP/caches/bmpcachepersister.hpp \
    src/mod/rdp/params/rdp_session_probe_params.hpp \
    src/utils/fileutils.hpp \
    src/utils/cfgloader.hpp \
    src/utils/primitives/primitives_sse2.hpp \
    src/transport/file_transport.hpp ;
do
    disable_sources+=" --disable-src $f"
done

./tools/bjam/gen_targets.py \
    --main $d/src/main \
    --src $d/src/red_emscripten \
    --src $d/src/redjs \
    --src $d/src/red_channels \
    --deps-src src/mod/rdp/new_mod_rdp.hpp,$d/src/red_channels/\*.cpp \
    --include $d/src/ \
    --src-system emscripten \
    --lib '' \
    --test $d/tests \
    $disable_sources \
| sed -E '
    /^  <variant>[^:]+:<library>dl$|^  <(covfile|variant)|^  \$\(GCOV_NO_BUILD\)|\.coverage ;$/d;
    s/^exe /exe-js /;t
    s@^test-run '$d'/@test-run-js @;t
    s/^obj ([^.]+).o/objjs \1.bc/;ta
    s/^  <library>(.*)\.o/  \1.bc/;ta
    s/^  (.*)\.o/  \1.bc/;ta
    s/^  <library>(.*)/  \1.bc/;ta
    s/^  \$\(EXE_DEPENDENCIES\)/:\n&/;t
    :a
    s@ : src/@ : $(REDEMPTION_SRC_PATH)/@g
    s@ : tests/@ : $(REDEMPTION_TEST_PATH)/@g
    s@ : projects/redemption_configs/@ : $(REDEMPTION_CONFIG_PATH)/@g
    s@ '$d'/@ @g
'
# s@^(objjs src/main/[^.]+\.bc : src/[^ ]+) ;$@\1 : <cxxflags>-fno-rtti\&\&-frtti ;@
exit ${PIPESTATUS[0]}
