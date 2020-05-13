The cpp files in this folder were written by me. The files and their header files were already created before I started, therefore the parameters of the functions were specified. 


In the build, there are three files that can be run. 

./rays runs a ray on triangle mesh intersection test

You can use the default test, or specify an obj like this: 

./rays ../data/rubber-ducky.obj

./distances runs a point cloud distance queries test

You can use the default test, or specify the number of points and the queries like this:

./distances 10000000 1000000


./intersections runs a triangle mesh collision/intersection test

You can use the default test, or specify two obj meshes like this:

./intersections ../data/knight.obj ../data/cheburashka.obj




