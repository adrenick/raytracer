// csc473, assignment 1 sample file (RIGHT HANDED)

camera {
  location  <0, 0, 12>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

light_source {<-100, 100, 100> color rgb <0.75, 0.25, 0.25>
  area_light
  <100, 0, 100>, <0, 100, 0>, 10, 10
  }
light_source {<100, 100, 100> color rgb <0.0, 0.4, 0.75>
  area_light
  <100, 0, 100>, <0, 100, 0>, 10, 10
  }


// row 1

sphere { <-4, -4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.2>}
  finish {ambient 0.1 diffuse 0.9 refraction 1.0 ior 1.0}
}

sphere { <-2, -4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.4>}
  finish {ambient 0.1 diffuse 0.9 refraction 1.0 ior 1.0}
}

sphere { <0, -4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.6>}
  finish {ambient 0.1 diffuse 0.9 refraction 1.0 ior 1.0}
}

sphere { <2, -4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.8>}
  finish {ambient 0.1 diffuse 0.9 refraction 1.0 ior 1.0}
}

sphere { <4, -4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.9 refraction 1.0 ior 1.0}
}


// row 2

sphere { <-4, -2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.2>}
  finish {ambient 0.1 diffuse 0.7 refraction 1.0 ior 1.2}
}

sphere { <-2, -2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.4>}
  finish {ambient 0.1 diffuse 0.7 refraction 1.0 ior 1.2}
}

sphere { <0, -2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.6>}
  finish {ambient 0.1 diffuse 0.7 refraction 1.0 ior 1.2}
}

sphere { <2, -2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.8>}
  finish {ambient 0.1 diffuse 0.7 refraction 1.0 ior 1.2}
}

sphere { <4, -2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.7 refraction 1.0 ior 1.2}
}


// row 3

sphere { <-4, 0, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.2>}
  finish {ambient 0.1 diffuse 0.5 refraction 1.0 ior 1.4}
}

sphere { <-2, 0, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.4>}
  finish {ambient 0.1 diffuse 0.5 refraction 1.0 ior 1.4}
}

sphere { <0, 0, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.6>}
  finish {ambient 0.1 diffuse 0.5 refraction 1.0 ior 1.4}
}

sphere { <2, 0, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.8>}
  finish {ambient 0.1 diffuse 0.5 refraction 1.0 ior 1.4}
}

sphere { <4, 0, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.5 refraction 1.0 ior 1.4}
}


// row 4

sphere { <-4, 2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.2>}
  finish {ambient 0.1 diffuse 0.3 refraction 1.0 ior 1.6}
}

sphere { <-2, 2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.4>}
  finish {ambient 0.1 diffuse 0.3 refraction 1.0 ior 1.6}
}

sphere { <0, 2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.6>}
  finish {ambient 0.1 diffuse 0.3 refraction 1.0 ior 1.6}
}

sphere { <2, 2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.8>}
  finish {ambient 0.1 diffuse 0.3 refraction 1.0 ior 1.6}
}

sphere { <4, 2, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.3 refraction 1.0 ior 1.6}
}


// row 5

sphere { <-4, 4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.2>}
  finish {ambient 0.1 diffuse 0.1 refraction 1.0 ior 1.8}
}

sphere { <-2, 4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.4>}
  finish {ambient 0.1 diffuse 0.1 refraction 1.0 ior 1.8}
}

sphere { <0, 4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.6>}
  finish {ambient 0.1 diffuse 0.1 refraction 1.0 ior 1.8}
}

sphere { <2, 4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 0.8>}
  finish {ambient 0.1 diffuse 0.1 refraction 1.0 ior 1.8}
}

sphere { <4, 4, 0>, 0.8
  pigment { color rgb <1.0, 1.0, 1.0, 1.0>}
  finish {ambient 0.1 diffuse 0.1 refraction 1.0 ior 1.8}
}


// plane

plane {<0, 1, 0>, -6
  pigment {color rgb <0.4, 0.2, 0.6>}
  finish {ambient 0.4 diffuse 0.8}
}