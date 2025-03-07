const redemptionLoadModule = function(Module, window)
{
    const HEAPU8 = Module.HEAPU8;
    const HEAP16 = Module.HEAP16;

    const identity = function(cb, thisp) {
        return function(...args) {
            return cb.call(thisp, ...args);
        };
    };

    const wCb_em2js_ImageData = function(cb, thisp) {
        return function(idata, w, h, ...args) {
            const data = HEAPU8.subarray(idata, idata + w * h * 4);
            // TODO Uint8ClampedArray(data) -> data ?
            const image = new ImageData(new Uint8ClampedArray(data), w, h);
            return cb.call(thisp, image, ...args);
        };
    };

    const wCb_em2js_U8p = function(cb, thisp) {
        return function(idata, len, ...args) {
            const data = HEAPU8.subarray(idata, idata + len);
            return cb.call(thisp, data, ...args);
        };
    };

    const noop = function(){};

    // { funcname: [wrapCreator, defaultFunction], ... }
    const wrappersGd = {
        setCachedImageSize: identity,
        cachedImage: wCb_em2js_ImageData,
        drawCachedImage: identity,
        drawImage: wCb_em2js_ImageData,

        drawRect: identity,
        drawSrcBlt: identity,
        drawLineTo: identity,
        drawDestBlt: identity,

        drawPolyline: function(cb, thisp) {
            return function(xStart, yStart, numDeltaEntries, deltaEntries, penColor) {
                const deltas = HEAP16.subarray(deltaEntries, deltaEntries + numDeltaEntries * 2);
                cb.call(thisp, xStart, yStart, deltas, penColor);
            };
        },

        drawPatBlt: identity,
        drawPatBltEx: function(cb, thisp) {
            return function(x, y, w, h, rop, backColor, foreColor, brush) {
                const brushData = HEAPU8.subarray(brush, brush + 8);
                cb.call(thisp, x, y, w, h, rop, backColor, foreColor, brushData);
            };
        },


        setPointer: wCb_em2js_ImageData,
        newPointer: wCb_em2js_ImageData,
        cachedPointer: identity,

        resizeCanvas: identity,
    };

    const wrappersFront = {
        random: wCb_em2js_U8p,
    };

    const wrapEvents = function(wrappedEvents, wrappers, events, defaultCb) {
        for (const eventName in wrappers) {
            const wrapCb = wrappers[eventName];
            const cb = events[eventName];
            wrappedEvents[eventName] = cb ? wrapCb(cb, events) : defaultCb;
        }
    };


    class RDPClient {
        constructor(socket, width, height, events, username, password, disabled_orders, verbosity) {
            const rdpEvents = {};
            wrapEvents(rdpEvents, wrappersGd, events, noop);
            wrapEvents(rdpEvents, wrappersFront, events, undefined);
            if (!rdpEvents.random) {
                rdpEvents.random = function(idata, len) {
                    const data = HEAPU8.subarray(idata, idata + len);
                    window.crypto.getRandomValues(data);
                }
            }

            this.native = new Module.RdpClient(
                rdpEvents, width, height,
                username || "", password || "",
                disabled_orders || 0,
                verbosity || 0,
            );
            this.socket = socket;
            this._channels = [];
        }

        close() {
            this.socket.close();
        }

        start() {
            this.native.sendFirstPacket();
            this.sendBufferedData();
        }

        delete() {
            for (const channel of this._channels) {
                channel.delete();
            }
            this.native.delete();
        }

        getCallback() {
            return this.native.getCallbackAsVoidPtr();
        }

        addChannel(channel) {
            this._channels.push(channel);
            this.native.addChannelReceiver(channel.getChannelReceiver());
        }

        sendUnicode(unicode, flags) {
            this.native.sendUnicode(unicode, flags);
            this.sendBufferedData();
        }

        sendScancode(key, flags) {
            this.native.sendScancode(key, flags);
            this.sendBufferedData();
        }

        sendMouseEvent(flag, x, y) {
            this.native.sendMouseEvent(flag, x, y);
            this.sendBufferedData();
        }

        sendBufferedData() {
            const out = this.native.getSendingData();
            if (out.length) {
                this.socket.send(out);

                // let text = "";
                // console.log('Received Binary Message of ' + out.length + ' bytes');
                // for (let byte of out) {
                //     text += ":" + (byte+0x10000).toString(16).substr(-2);
                // }
                // this.counter = (this.counter || 0) + 1
                // console.log(this.counter, "Send: " + text);

                this.native.clearSendingData();
            }
        }

        addReceivingData(data) {
            this.native.addReceivingData(data);
        }
    };

    const wrappersPlayer = {
        setPointerPosition: identity,
        setTime: identity,
    };

    const resultFuncs = {
        RDPClient: RDPClient,
        newRDPSocket: function(url) {
            const socket = new WebSocket(url, "RDP");
            socket.binaryType = 'arraybuffer';
            return socket;
        },
        newWrmPlayer: function(events) {
            const playerEvents = {};
            wrapEvents(playerEvents, wrappersGd, events, noop);
            wrapEvents(playerEvents, wrappersPlayer, events, noop);
            return new Module.WrmPlayer(playerEvents);
        }
    };

    const addChannelClass = (ChannelClassName, wrappers) => {
        resultFuncs['new' + ChannelClassName] = function(cb, events, ...channelArgs) {
            wrapEvents(events, wrappers, events, noop);
            const chann = new Module[ChannelClassName](cb, events, ...channelArgs);
            const setChann = events['setEmcChannel'];
            if (setChann) {
                setChann.call(events, chann);
            }
            return chann;
        };
    };

    addChannelClass('ClipboardChannel', {
        setGeneralCapability: identity,
        formatListStart: identity,
        formatListFormat: wCb_em2js_U8p,
        formatListStop: identity,
        formatDataResponse: wCb_em2js_U8p,
        formatDataResponseFileStart: identity,
        formatDataResponseFile: wCb_em2js_U8p,
        formatDataResponseFileStop: identity,
        formatDataRequest: identity,
        fileContentsRequest: identity,
        fileContentsResponse: wCb_em2js_U8p,
        receiveResponseFail: identity,
        lock: identity,
        unlock: identity,
        free: identity,
    });

    addChannelClass('CustomChannel', {
        receiveData: wCb_em2js_U8p,
        free: identity,
    });

    return resultFuncs;
};
