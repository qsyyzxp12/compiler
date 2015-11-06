./parser sample/$1
dot AST_Graph.gv -Tpng -o output.png
gnome-open output.png
