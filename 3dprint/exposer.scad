$fn=64;
bsl=1/100;

part="bottom";//[NOSTL_assembly,bottom,foot]
wall=1.2;
angle=10;
thickness=8;
hole=3;
slack=1;

led_width=10.5;
led_length=50;
led_depth=1.2;
led_dist=16.5;
led_strips=4;

box_size=[led_length+4*thickness+2*slack,led_dist*(1+led_strips)];
length=box_size[1]-thickness;

module bottom() {
  translate(-box_size/2) cube([box_size[0],box_size[1],wall]);
  translate([0,-box_size[1]/2,wall]) rotate([90,0,90])linear_extrude(height=led_length,center=true) 
  difference() {
    square([box_size[1],led_depth]);
    for (shift=[led_dist:led_dist:box_size[1]-1]) translate([shift,0]) polygon([[-led_width/2,0],[led_width/2,0],[0,led_width/2]]);
  }
  for (xflip=[[0,0],[1,0]],yflip=[[0,0],[0,1]]) mirror(xflip) mirror(yflip) translate(-box_size/2) eyelet();
}

module eyelet() {
  difference() {
    union() {
      translate([thickness/2,0,wall])cube([thickness,thickness/2,thickness+slack]);
      translate([thickness/2,0,wall])cube([thickness,thickness,thickness/2+slack]);
      translate([thickness/2,thickness/2,wall+thickness/2+slack])rotate([0,90,0])cylinder(d=thickness,h=thickness);

    }
    translate([thickness/2-bsl,thickness/2,wall+thickness/2+slack])rotate([0,90,0])cylinder(d=hole,h=thickness+2*bsl);
  }
}

module foot() {
  difference() {
    hull() {
      cylinder(d=thickness,h=thickness);
      translate([length-thickness,0,0]) cylinder(d=thickness,h=thickness);
    }
  translate([0,0,-bsl])cylinder(d=hole,h=thickness+2*bsl);
  rotate([0,0,angle])translate([-thickness/2-bsl,-length/2,thickness/2]) cube([thickness+2*bsl,length,thickness]);
  translate([-thickness/2-bsl,-length/2,thickness/2]) cube([thickness+2*bsl,length,thickness]);
  }
}
if (part=="foot") foot();
if (part=="bottom") bottom();
if (part=="NOSTL_assembly") {
  bottom();
  translate([2*thickness,thickness/2,wall+thickness/2])
  translate(-box_size/2) rotate([angle,0,0])rotate([0,-90,0])foot();

}