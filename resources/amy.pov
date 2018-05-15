// cpe473, triangle (RIGHT HANDED)
//0.301, 0.313, 0.909
camera {
  location  <0, 0, 7>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}

//light_source {<320, 100, 100> color rgb <0.5, 0.5, 0.5>}
//light_source {<-320, 100, 100> color rgb <0.5, 0.5, 0.5>}
//light_source {<-100, 100, 100> color rgb <0.75, 0.25, 0.25>}
//light_source {<100, 100, 100> color rgb <0.0, 0.4, 0.75>}

//light_source {<-100, 100, 100> color rgb <1, 0.353, 0.592>}
//light_source {<100, 100, 100> color rgb <0.443, 0.314, 0.909>}

light_source {<-75, 100, 100> color rgb <0.875, 0.3015, 0.421>}
light_source {<75, 100, 100> color rgb <0.2215, 0.357, 0.8295>}


triangle {
  <-.001,1, 0 >,
  <-.001, -.3,3 >,
  <1,-.3, 0 >
  pigment {color rgb <.329, .918, 1, .2>}
  finish {ambient 0.3 diffuse 0.4}
}

triangle {
  <0,1, 0 >,
  <-1, -.3,0 >,
  <0,-.3, 3 >
  pigment {color rgb <.329, .918, 1, .2>}
  finish {ambient 0.3 diffuse 0.4}
}

triangle {
  <-1, -.3,0 >,
  <0,-1.3, 0 >,
  <0,-.3, 3 >
  pigment {color rgb <.329, .918, 1, .2>}
  finish {ambient 0.3 diffuse 0.4}
}

triangle {
  <0,-.3, 2 >,
  <0,-1.3, 0 >,
  <1, -.3,0 >
  pigment {color rgb <.329, .918, 1, .2>}
  finish {ambient 0.3 diffuse 0.4}
}

sphere { <.7, 0, 5>, 0.2

  pigment {color rgbf <1, 1, 1, .8>}
  finish {ambient 0.2 diffuse 0.4 reflection 0.2 refraction 1.0 ior 1.33}
}

sphere { <-.7, 0, 5>, 0.2

  pigment {color rgbf <1, 1, 1, .8>}
  finish {ambient 0.2 diffuse 0.4 reflection 0.2 refraction 1.0 ior 1.33}
}

sphere { <0, 0, 5>, 0.2

  pigment {color rgbf <1, 1, 1, .8>}
  finish {ambient 0.2 diffuse 0.4 reflection 0.2 refraction 1.0 ior 1.33}
}

sphere { <0, 0.65, 5>, 0.2

  pigment {color rgbf <1, 1, 1, .8>}
  finish {ambient 0.2 diffuse 0.4 reflection 0.2 refraction 1.0 ior 1.33}
}

sphere { <0, -0.65, 5>, 0.2

  pigment {color rgbf <1, 1, 1, .8>}
  finish {ambient 0.2 diffuse 0.4 reflection 0.2 refraction 1.0 ior 1.33}
}

//0.914, 0.361, 1.0
plane {<0, 1, 0>, -4
  pigment {color rgb <0.414, 0.0, 0.5>}
  finish {ambient 0.3 diffuse 0.8}
}