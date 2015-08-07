//edges.vert

varying vec3 vertNormal;
varying vec4 vertPoint;

void main(){
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	vertNormal = gl_NormalMatrix*gl_Normal;
	vertPoint = gl_ModelViewMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}