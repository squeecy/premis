import numpy as np
import glm
import pygame as pg
import pywavefront

class Cube:
    def __init__(self, app):
        self.app = app
        self.ctx = app.ctx
        self.vbo = self.get_vbo()
        self.shader = self.get_shader_program('default')
        self.vao = self.get_vao()
        self.m_model_pitch = self.get_model_pitch_matrix()
        self.m_model_roll = self.get_model_roll_matrix()
        self.texture = self.get_texture(path='resources/textures/Livery.png')
        self.on_init()


    def on_init(self):
        self.shader['u_texture_0'] = 0
        self.texture.use()
        self.shader['m_proj'].write(self.app.camera.m_proj)
        self.shader['m_view'].write(self.app.camera.m_view)
        self.shader['m_model_pitch'].write(self.m_model_pitch)
        self.shader['m_model_roll'].write(self.m_model_roll)

    def get_texture(self, path):
        texture = pg.image.load(path).convert()
        texture = self.ctx.texture(size=texture.get_size(), components=3, data=pg.image.tostring(texture, 'RGB'))
        return texture

    def render(self):
        self.update()
        self.vao.render()

    def update(self):
        m_model_pitch = glm.rotate(self.m_model_pitch, -glm.radians(self.app.pitch), glm.vec3(1, 0, 0))
        m_model_roll = glm.rotate(self.m_model_roll, glm.radians(self.app.roll), glm.vec3(0, 0, 1))
        self.shader['m_model_pitch'].write(m_model_pitch)
        self.shader['m_model_roll'].write(m_model_roll)
    
    def get_vao(self):
        vao = self.ctx.vertex_array(self.shader, [(self.vbo, '2f 3f 3f', 'in_texcoord_0', 'in_normal','in_position')])
        return vao
    def rocket_vap(self):
        rocket_vao = self.ctx.vertex_array(self.shader, [(self.vbo, '2f 3f', 'in_texcoord_0', 'in_position')])

    def get_rocket_vertex_data(self):
        objs = pywavefront.Wavefront('resources/obj/premis_model.obj')
        obj = objs.materials.popitem()[1]
        rocket_vertex_data = obj.vertices
        rocket_vertex_data = np.array(rocket_vertex_data, dtype='f4')
        return rocket_vertex_data

    def get_vertex_data(self):
        vertices = [(-1, -1, 1), (1, -1, 1), (1, 1, 1), (-1, 1, 1), 
                     (-1, 1, -1), (-1, -1, -1), (1, -1, -1), (1, 1, -1)] #square vertices
        
        indices = [(0, 2, 3), (0, 1, 2),
                   (1, 7, 2), (1, 6, 7),
                   (6, 5, 4), (4, 7, 6),
                   (3, 5, 4), (3, 5, 0),
                   (3, 7, 4), (3, 2, 7),
                   (0, 6, 1), (0, 5, 6)
                  ]
        vertex_data = self.get_data(vertices, indices)

        tex_coord = [(0, 0), (1, 0), (1,1), (0, 1)]

        tex_coord_indices = [(0, 2, 3), (0, 1, 2),
                              (0, 2, 3), (0, 1, 2),
                              (0, 1, 2), (2, 3, 0),
                              (2, 3, 0), (2, 0, 1),
                              (0, 2, 3), (0, 1, 2),
                              (3, 1, 2), (3, 0, 1)
                             ]

        tex_coord_data = self.get_data(tex_coord, tex_coord_indices)

        vertex_data = np.hstack([tex_coord_data, vertex_data])
        
        return vertex_data 

        
    
    @staticmethod
    def get_data(vertices, indices):
        data = [vertices[ind] for triangle in indices for ind in triangle]
        return np.array(data, dtype='f4')

    def get_vbo(self):
        vertex_data = self.get_rocket_vertex_data()
        vbo = self.ctx.buffer(vertex_data)
        return vbo


    def get_shader_program(self, shaderName):
        with open(f'resources/shaders/{shaderName}.vert') as file:
            vertex_shader = file.read()
        with open(f'resources/shaders/{shaderName}.frag') as file:
            fragment_shader = file.read()
        program = self.ctx.program(vertex_shader=vertex_shader, fragment_shader=fragment_shader)
        return program 

    
    def get_model_pitch_matrix(self):
        m_model_pitch = glm.mat4()
        return m_model_pitch

    def get_model_roll_matrix(self):
        m_model_roll = glm.mat4()
        return m_model_roll


    def remove(self):
        self.vbo.release()
        self.get_shader_program.release()
        self.vao.release()

class RocketVBO(Cube):
    def __init__(self, app):
        super().__init__(app)
        self.format = '2f, 3f, 3f'
        self.attribs = ['in_textcoord_0', 'in_normal', 'in_position']

    def get_vertex_data(self):
        objs = pywavefront.Wavefront('resources/obj/premis_model.obj')
        obj = objs.materials.popitem()[1]
        vertex_data = obj.vertices
        vertex_data = np.array(vertex_data, dtype='f4')
        return vertex_data