//edges.frag

varying vec3 vertNormal;
varying vec4 vertPoint;

uniform sampler2D texture1;
uniform float maxX;
uniform float minX;
uniform float maxY;
uniform float minY;
uniform float maxZ;
uniform float minZ;


float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(){
	//float zdiff = maxZ-minZ;
	//if (zdiff < 0.0){
	//	zdiff = -1.0*zdiff;
	//}
	//vec3 cameraVector = vec3(0, 0, 10);
	//float camNormDot = dot(vertNormal, cameraVector);
	//gl_FragColor = texture2D(texture1, gl_TexCoord[0].st);


	//vec2 range = vec2(0.0, 2.0);
	//float randomNum = rand(range);
	float testprod = cos((vertPoint.x + vertPoint.y)/2.0)/4.0;

	if(!(vertNormal.z >= (-1.0*testprod) && vertNormal.z <= testprod)){
		gl_FragColor = texture2D(texture1, gl_TexCoord[0].st);
	}
	if(gl_FragColor.rgb == vec3(0.0, 0.0, 0.0)){
		discard;
	}
}