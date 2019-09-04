#!/usr/bin/env python

import numpy as np
from bokeh.plotting import figure, output_file, show
from bokeh.models import ColumnDataSource
from bokeh.models.widgets import TextInput
from bokeh.layouts import gridplot

from math import pi


from bokeh.io import curdoc


# A, B, a, b = map(float,list(input().split()))


# print(x,y)
fig = figure(tools="crosshair,pan,reset,save,wheel_zoom", title="Lab1",
             x_axis_label='x',
             y_axis_label='y')


a = TextInput(title="a", value='1')
b = TextInput(title="b", value='2')
A = TextInput(title="A", value='0')
B = TextInput(title="B", value='360')

phi = np.arange(0.*pi/180, 360.*pi/180, 0.01)


source = ColumnDataSource(data=dict(x=phi - np.sin(phi),
                                    y=-np.cos(phi)))

fig.line(x="x", y="y",
         source=source,
         line_width=2,
         legend="x = a*phi - b*sin(phi)\ny = a - b*cos(phi)")

fig.xaxis.axis_label = "x"
fig.yaxis.axis_label = "y"
fig.title.text = "Lab1"

def update_source(attr, old, new):
    if float(a.value) >= float(b.value):
        fig.title.text = "Wrong arguments!\na>=b"
        return
    else:
        fig.title.text = "Plotting"
    try:
        phi = np.arange(float(A.value)*pi/180, float(B.value)*pi/180, 0.01)
        x = float(a.value)*phi - float(b.value)*np.sin(phi)
        y = float(a.value) - float(b.value)*np.cos(phi)
        source.data = dict(x=x, y=y)
        print("source updated")
    except ValueError:
        pass

# def update_dots(attr, old, new):
#     # global phi
#     phi.data = np.arange(float(A.value)*pi/180, float(B.value)*pi/180, 0.01)
#     print("data updated")
#     update_source(attr, old, new)


for w in [a, b, A, B]:
    w.on_change('value', update_source)

# for w in [A, B]:
#     w.on_change('value', update_dots)

grid = gridplot([[a, b], [A, B], [fig]])

# show(grid)
curdoc().add_root(grid)
