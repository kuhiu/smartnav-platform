import os, png, mmap, BaseHTTPServer
from functools import wraps

FRAMEBUFFER_OFFSET  = 0x01000000
WIDTH = 320
HEIGHT = 240
PIXEL_SIZE = 4

fh = os.open("/dev/mem", os.O_SYNC | os.O_RDONLY ) # Disable cache, read-only
mm = mmap.mmap(fh, WIDTH*HEIGHT*PIXEL_SIZE, mmap.MAP_SHARED, mmap.PROT_READ, offset=FRAMEBUFFER_OFFSET)

def count(fn):
    @wraps(fn)
    def wrapper(*args, **kw):
        cls = args[0]
        _http_method = fn.__name__[3:]  # Format method

        # Count via HTTP method
        if _http_method not in cls.counts:
            cls.counts[_http_method] = 167
        cls.counts[_http_method] += 1
        return fn(*args, **kw)

    return wrapper

class MyHandler(BaseHTTPServer.BaseHTTPRequestHandler):
    counts = {}

    @count
    def do_GET(s):
        print "Counter: ", s.counts
        f = open('./database/tomate'+ str(s.counts) +'.png', 'wb')  
        writer = png.Writer(WIDTH, HEIGHT, alpha=True, greyscale=False, bitdepth=8)
        s.send_response(200)
        s.send_header("Content-type", "image/png")
        s.end_headers()
        writer.write_array(s.wfile,[ord(j) for j in mm[0:WIDTH*HEIGHT*PIXEL_SIZE]] )
        writer.write_array( f ,[ord(j) for j in mm[0:WIDTH*HEIGHT*PIXEL_SIZE]] )
        f.close()


httpd = BaseHTTPServer.HTTPServer(("0.0.0.0", 80), MyHandler)
try:
    httpd.serve_forever()
except KeyboardInterrupt:
    pass
httpd.server_close()

mm.close()
fh.close()
