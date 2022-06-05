import os, png, mmap, time
from http.server import BaseHTTPRequestHandler, HTTPServer

FRAMEBUFFER_OFFSET  = 0x01000000
WIDTH = 320
HEIGHT = 240
PIXEL_SIZE = 4

fh = os.open("/dev/mem", os.O_SYNC | os.O_RDONLY ) # Disable cache, read-only
mm = mmap.mmap(fh, WIDTH*HEIGHT*PIXEL_SIZE, mmap.MAP_SHARED, mmap.PROT_READ, offset=FRAMEBUFFER_OFFSET)

class MyHandler(BaseHTTPRequestHandler):
    def do_GET(s): 
        writer = png.Writer(WIDTH, HEIGHT, alpha=True, greyscale=False, bitdepth=8)
        s.send_response(200)
        s.send_header('Cache-Control', 'no-cache')
        s.send_header("Content-Type", "multipart/x-mixed-replace; boundary=--jpgboundary")
        s.end_headers()
        output="--jpgboundary"
        while True:
            s.wfile.write(output.encode())
            s.send_header('Content-type','image/jpeg')
            s.send_header('Content-length',WIDTH*HEIGHT*PIXEL_SIZE)
            s.end_headers()
            writer.write_array(s.wfile,[j for j in mm[0:WIDTH*HEIGHT*PIXEL_SIZE]])
            #time.sleep(3)
  
httpd = HTTPServer(("0.0.0.0", 81), MyHandler)
try:
    httpd.serve_forever()
except KeyboardInterrupt:
    pass
httpd.server_close()

mm.close()
fh.close()
