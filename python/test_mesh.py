# -*- coding: utf-8 -*-
"""
Created on Mon Apr 27 16:14:39 2015

@author: paul

surface : 缺省值，绘制曲面
wireframe : 绘制边线，将dphi, dtheta的改为较大值，例如pi/20之后，调用 ：

"""
from numpy import *
from mayavi import mlab

# Create the data.
dphi, dtheta = pi/20.0, pi/20.0
[phi,theta] = mgrid[0:pi+dphi*1.5:dphi,0:2*pi+dtheta*1.5:dtheta]
m0 = 4; m1 = 3; m2 = 2; m3 = 3; m4 = 6; m5 = 2; m6 = 6; m7 = 4;
r = sin(m0*phi)**m1 + cos(m2*phi)**m3 + sin(m4*theta)**m5 + cos(m6*theta)**m7
x = r*sin(phi)*cos(theta)
y = r*cos(phi)
z = r*sin(phi)*sin(theta)

# View it.
#s = mlab.mesh(x, y, z, representation="wireframe", line_width=1.0 )
s = mlab.mesh(x, y, z, representation="surface", line_width=1.0 )

mlab.show()