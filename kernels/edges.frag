//edges.frag

varying vec3 vertNormal;
varying vec4 vertPoint;
uniform sampler2D texture1;
uniform vec3 _WorldSpaceCameraPos;


float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(){
	vec3 cameraVector = normalize(_WorldSpaceCameraPos-vertPoint.xyz);
	float camNormDot = dot(vertNormal, cameraVector);
	gl_FragColor = texture2D(texture1, gl_TexCoord[0].st);

	//vec2 range = vec2(0.0, 10);
	//float randomNum = rand(range);

	if(camNormDot >= 0.0 && camNormDot <= 0.5){
		gl_FragColor = vec4(0.2, 0.2, 0.2, 1.0);
	}
}