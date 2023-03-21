import serial
import pygame as pg
import moderngl as mgl
import sys
from pygame.locals import *

#my files
from draw import*
from camera import*



#global variables for serial reading
SERIAL_PORT = 'COM3'
ser = serial.Serial(SERIAL_PORT)
ser.flushInput()

WIDTH = 800
HEIGHT = 800

class GraphicsEngine:
    def __init__(self, winSize = (WIDTH, HEIGHT)):
        pg.init()

        self.WIN_SIZE = winSize
        pg.display.gl_set_attribute(pg.GL_CONTEXT_MAJOR_VERSION, 3)
        pg.display.gl_set_attribute(pg.GL_CONTEXT_MINOR_VERSION, 3)
        pg.display.gl_set_attribute(pg.GL_CONTEXT_PROFILE_MASK, pg.GL_CONTEXT_PROFILE_CORE)

        pg.display.set_mode(self.WIN_SIZE, flags=pg.OPENGL | pg.DOUBLEBUF)
        pg.display.set_caption("3dViewer")
        self.pitch = 0
        self.roll = 0
        self.ctx = mgl.create_context()
        self.ctx.enable(flags=mgl.DEPTH_TEST | mgl.CULL_FACE)
        self.clock = pg.time.Clock()   
        self.camera = Camera(self)
        self.scene = Cube(self)

    def check_events(self):
        for event in pg.event.get():
            if event.type == pg.QUIT or (event.type == pg.KEYDOWN and event.key == pg.K_ESCAPE):
                self.scene.remove()
                pg.quit()
                sys.exit()

        # read serial data
    def readData(self)-> str:
        ser.flushInput()
        ser_bytes = ser.readline()
        return str(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))

    # convert serial data
    def setData(self)-> None:
        #format the data into a list
        data = self.readData().split(',')
        self.pitch = -float(data[2]) #pitch
        self.roll = float(data[1]) #roll
        az = float(data[0]) #yaw
        ser.flushInput()
        print(self.pitch)

    def render(self):
        self.ctx.clear(color=(8.0/255.0, 9.0/255.0, 10.0/255.0))
        self.scene.render()
        pg.display.flip()

    def run(self):
        while True:
            self.setData()
            self.check_events()
            self.render()
            self.clock.tick(60)

if __name__ == '__main__':
    app = GraphicsEngine()
    app.run()
