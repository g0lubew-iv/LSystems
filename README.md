<h1>LSystems and OpenGL</h1>

Coursework. Mentor: Polevoy D. V.

Rules definitions (according to Paul Bourke):

| Character | Meaning                                            |
|----------:|----------------------------------------------------|
|         F | Move forward by line length drawing a line         |
|         f | Move forward by line length without drawing a line |
|         + | Turn left by turning angle                         |
|         - | Turn right by turning angle                        |
|        \[ | Push current drawing state onto stack              |
|        \] | Pop current drawing state from the stack           |

<h3>Building</h3>
Dependencies:
1. GLFW
2. Glad
3. Glm
4. Boost

<h3>Using</h3>

```
l_system_drawer -h
```

E.g. command as follows...

```
./l_system_drawer -gen 7 -rot 22.5 -axm "F" -rul "F->FF-[XY]+[XY]" -rul "X->+FY" -rul "Y->-FX"
```
... will produce window with this plant:

![plot](./example1.png)

Another one:

```
./l_system_drawer -gen 10 -rot 120 -axm "F+F+F" -rul "F->F-F+F"
```

![plot](./example2.png)