# QGRAPH

A C graphing utility that... graphs functions.

### Features

- [x] Resizable graph using arrow keys
- [x] A basic smoothing function, toggleable with space
- [x] Saving screenshots of graphs, using enter
- [ ] A function parser to turn strings into functions
- [ ] Negative x- and y-values
- [ ] Moving around in the graph window
- [ ] Tracing/getting the value at a point
- [ ] Rendering individual labelled points

Ultimately, this is not a serious project from me, just one of those mini-projects to bang out and keep the juices flowing. Don't expect regular updates, or for me to complete the feature list -- just use Desmos!

### Usage

To install, run `make install` -- this will compile the executable and run the setup script, which for now just creates a folder for screenshots.

If you fancy editing the code, `make run` and `make build` are also included in the Makefile.

**To edit which function is displayed, edit the function `function()` in main.c.**

### Controls

- `← ↑ → ↓` to resize the graph window (current limits: evaluation 1 - 15 on each axis)
- `SPACE` to toggle smoothing -- this can make some steeper functions look significantly better, but functions with a constant slope may look chunky. It's toggleable for a reason.
- `ENTER` to save a screenshot of the graph to `./imgs/`. Will save prefixed with with the timestamp and dimensions of the graph.
- `ESC` to exit the window.
