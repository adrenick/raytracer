camera {
  location  <0, 0, 20>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}


light_source {<-100, 100, 100> color rgb <1.5, 1.5, 1.5>

}

sphere { <-7, 2, 0>, 4
  pigment { color rgbf <1.0, 1.0, 1.0, 0.95> }
  finish { ambient 0.02 diffuse 0.4 specular 10.0 roughness 0.03 refraction 1.0 ior 1.33 }
}

sphere { <0, 3, 0>, 3
  pigment { color rgbf <1.0, 1.0, 1.0, 0.95>}
  finish { ambient 0.02 diffuse 0.4 specular 10.0 roughness 0.03 refraction 1.0 ior 1.15 }
}

sphere { <5, 1, 0>, 3.5
  pigment { color rgbf <1.0, 1.0, 1.0, 0.95>}
  finish { ambient 0.02 diffuse 0.4 specular 10.0 roughness 0.03 refraction 1.0 ior 1.33 }
}

plane {<0, 1, 0>, -4
  pigment { color rgb <0.2, 0.4, 0.7> }
  finish { ambient 0.4 diffuse 0.8 }
}