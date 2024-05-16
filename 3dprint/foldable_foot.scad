$fn=64;
bissl=1/100;

part="NOSTL_assembly";//[NOSTL_assembly,hinge,foot]
wall=3;
angle=10;
length=60;
thickness=10;
hole=3;
module hinge() {
  difference() {
    union() {
      //cube([3*thickness,thickness,wall]);
      hull() {
        translate([thickness/2,thickness/2,0])cylinder(d=thickness,h=wall);
        translate([5*thickness/2,thickness/2,0])cylinder(d=thickness,h=wall);
      }
      translate([thickness,0,wall])cube([thickness/2,thickness/2,thickness]);
      translate([thickness,0,wall])cube([thickness/2,thickness,thickness/2]);
      translate([thickness,thickness/2,wall+thickness/2])rotate([0,90,0])cylinder(d=thickness,h=thickness/2);
    }
    translate([thickness/2,thickness/2,-bissl])cylinder(d=hole,h=wall+2*bissl);
    translate([5*thickness/2,thickness/2,-bissl])cylinder(d=hole,h=wall+2*bissl);
    translate([thickness-bissl,thickness/2,wall+thickness/2])rotate([0,90,0])cylinder(d=hole,h=thickness/2+2*bissl);
  }
}
module foot() {
  difference() {
    hull() {
      cylinder(d=thickness,h=thickness);
      translate([length-thickness,0,0]) cylinder(d=thickness,h=thickness);
    }
  translate([0,0,-bissl])cylinder(d=hole,h=thickness+2*bissl);
  rotate([0,0,angle])translate([-thickness/2-bissl,-length/2,thickness/2]) cube([thickness+2*bissl,length,thickness]);
  }
}
if (part=="hinge") hinge();
if (part=="foot") foot();
if (part=="NOSTL_assembly") {
  translate([2*thickness,thickness/2,wall+thickness/2])rotate([angle,0,0])rotate([0,-90,0])foot();
  hinge();
}