//edges.frag

varying vec3 vertNormal;
varying vec4 vertPoint;

uniform sampler2D texture1;

void main(){
   float testprod = cos((vertPoint.x + vertPoint.y)/2.0)/3.5;

   if(!(vertNormal.z >= (-1.0*testprod) && vertNormal.z <= testprod)){
      gl_FragColor = texture2D(texture1, gl_TexCoord[0].st);
   }
   else
   {
      gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
   }
   if(gl_FragColor.rgb == vec3(0.0, 0.0, 0.0)){
      discard;
   }
}
