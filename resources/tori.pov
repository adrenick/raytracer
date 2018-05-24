// csc473, assignment 4 file

camera {
  location  <0, 1, 18>
  up        <0,  0.9985,  -0.0555>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}


light_source {<0, 50, 25> color rgb <1.8, 1.8, 1.5>}

// 
sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.153, 0.678, 0.776, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.3, 2.8, 0.3>
  rotate <0, 0, -45>
  translate <-7, -1, 0>
}

sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.153, 0.678, 0.776, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.3, 2.8, 0.3>
  rotate <0, 0, 45>
  translate <-7, -1, 0>
}

sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.153, 0.678, 0.776, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.3, 2.8, 0.3>
  rotate <0, 0, -90>
  translate <-7, -1, 0>
}

sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.153, 0.678, 0.776, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.3, 2.8, 0.3>
  rotate <0, 0, 90>
  translate <-7, -1, 0>
}

sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.153, 0.678, 0.776, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.3, 2.8, 0.3>
  rotate <0, 0, -180>
  translate <-7, -1, 0>
}

sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.153, 0.678, 0.776, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.3, 2.8, 0.3>
  rotate <0, 0, 180>
  translate <-7, -1, 0>
}

//*********
sphere { <0, 0, 0>, 1.0
  pigment { color rgb <1.0, 0.816, 0.176, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.5, 3, 0.5>
  rotate <0, 0, -45>
  translate <0, 3, 5>
}

sphere { <0, 0, 0>, 1.0
  pigment { color rgb <1.0, 0.816, 0.176, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.5, 3, 0.5>
  rotate <0, 0, 45>
  translate <0, 3, 5>
}

sphere { <0, 0, 0>, 1.0
  pigment { color rgb <1.0, 0.816, 0.176, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.5, 3, 0.5>
  rotate <0, 0, -90>
  translate <0, 3, 5>
}

sphere { <0, 0, 0>, 1.0
  pigment { color rgb <1.0, 0.816, 0.176, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.5, 3, 0.5>
  rotate <0, 0, 90>
  translate <0, 3, 5>
}

sphere { <0, 0, 0>, 1.0
  pigment { color rgb <1.0, 0.816, 0.176, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.5, 3, 0.5>
  rotate <0, 0, -180>
  translate <0, 3, 5>
}

sphere { <0, 0, 0>, 1.0
  pigment { color rgb <1.0, 0.816, 0.176, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.5, 3, 0.5>
  rotate <0, 0, 180>
  translate <0, 3, 5>
}

//*********
sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.286, 0.176, 0.647, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.3, 2.5, 0.3>
  rotate <0, 0, -45>
  translate <7, 0.5, -1>
}

sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.286, 0.176, 0.647, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.3, 2.5, 0.3>
  rotate <0, 0, 45>
  translate <7, 0.5, -1>
}

sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.286, 0.176, 0.647, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.3, 2.5, 0.3>
  rotate <0, 0, -90>
  translate <7, 0.5, -1>
}

sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.286, 0.176, 0.647, 0.5> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.3, 2.5, 0.3>
  rotate <0, 0, 90>
  translate <7, 0.5, -1>
}

sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.286, 0.176, 0.647, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.3, 2.5, 0.3>
  rotate <0, 0, -180>
  translate <7, 0.5, -1>
}

sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.286, 0.176, 0.647, 0.2> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6}
  scale <0.3, 2.5, 0.3>
  rotate <0, 0, 180>
  translate <7, 0.5, -1>
}

// Floor
plane { <0, 0, 1>, -4
  pigment {color rgb <0.487, 0.451, 0.565>}
  finish {ambient 0.4 diffuse 1.0 reflection 0.7}
  rotate <-90, 0, 0>
}

// Background
plane { <0, 0, 1>, -100
  pigment {color rgb <1.0, 0.988, 0.914>}
  finish {ambient 0.2 diffuse 0.4}
}