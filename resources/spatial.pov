
//translate all -6 z

//left side of h:
//translate x -1.6
//scale x: 0.2 y: 1.5 z: 0.2
//global then tx then s

//right side of h:
//translate x -0.7
//scale x: 0.2 y: 1.5 z: 0.2
//global then tx then s

//i
//translate x 0.35
//scale x: 0.2 y: 1.5 z: 0.2
//global then tx then s

//cross of h
//translate x -1.2 y 0.2
//rotate z 1.0
//scale x: 0.18 y: 0.8 z: 0.2
//global then tx then rotate then s

camera {
location  <0, 0, 14>
up        <0,  1,  0>
right     <1.5, 0,  0>
look_at   <0, 0, 0>}

light_source {<10, 10, 3> color rgb <1.0, 1.0, 1.0>}

// floor
plane {<0, 1, 0>, -5
  pigment {color rgb <0.2, 0.2, 0.8>}
  finish {ambient 0.4 diffuse 0.2 reflection 0.2}
}

// back wall on the right
plane {<0, -1, 0>, -30
  pigment {color rgb <0.0, 0.2, 0.2>}
  finish {ambient 0.4 diffuse 0.8 }
}

//left side of h
box { <-5, -5, -5>, <5, 5, 5>
  pigment { color rgb <1.0, 0.2, 1.0>}
  finish {ambient 0.2 diffuse 0.8}
  scale <0.2, 1.5, 0.2>
  translate <-6, 0, -6>
}

//right side of h
box { <-5, -5, -5>, <5, 5, 5>
  pigment { color rgb <1.0, 0.2, 1.0>}
  finish {ambient 0.2 diffuse 0.8}
  scale <0.2, 1.5, 0.2>
  translate <0, 0, -6>
}

//i
box { <-5, -5, -5>, <5, 5, 5>
  pigment { color rgb <1.0, 0.2, 1.0>}
  finish {ambient 0.2 diffuse 0.8}
  scale <0.2, 1.5, 0.2>
  translate <6, 0, -6>
}

//cross of h
box { <-5, -5, -5>, <5, 5, 5>
  pigment { color rgb <1.0, 0.2, 1.0>}
  finish {ambient 0.2 diffuse 0.8}
  scale <0.18, 1, 0.2>
  rotate <0, 0, 70>
  translate <-3, 1.4, -6>
}

