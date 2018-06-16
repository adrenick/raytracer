camera {
  location  <0, 0, 20>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}


light_source {<-50, 100, 100> color rgb <1.5, 1.5, 1.5>
  area_light
  <100, 0, 100>, <0, 100, 0>, 15, 15
}

sphere { <-7, 0, 0>, 3
  pigment { color rgbf <1.0, 1.0, 1.0, 0.95> }
  finish { ambient 0.02 diffuse 0.4 specular 10.0 roughness 0.03 refraction 1.0 ior 1.02 }
}

sphere { <0, 0, 0>, 3
  pigment { color rgbf <1.0, 1.0, 1.0, 0.95>}
  finish { ambient 0.02 diffuse 0.4 specular 10.0 roughness 0.03 refraction 1.0 ior 1.15 }
}

sphere { <8, 0, 0>, 3
  pigment { color rgbf <1.0, 1.0, 1.0, 0.95>}
  finish { ambient 0.02 diffuse 0.4 specular 10.0 roughness 0.03 refraction 1.0 ior 1.33 }
}

plane {<0, 1, 0>, -4
  pigment { color rgb <0.2, 0.4, 0.7> }
  finish { ambient 0.4 diffuse 0.8 }
}
