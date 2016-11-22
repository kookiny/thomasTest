#extension GL_ARB_texture_rectangle : enable
uniform sampler2DRect src, srcBlur, dstBlur;
uniform float multiplier;

void main() {
	vec2 pos = gl_TexCoord[0].st;	//declaracion de variable pos de corrdenadas de posición
	vec4 srcColorBlur = texture2DRect(srcBlur, pos);//crear un vec4f llamado srcColorBlur en funcion de srcBlur y pos
	if(srcColorBlur.r > 0.) { // don't copy anything black
		vec3 srcColor = texture2DRect(src, pos).rgb;//crear un color lamado srcColor en funcion de src y pos
		vec4 dstColorBlur = texture2DRect(dstBlur, pos);// crear un vec4f llamado dstColorBlur en funcion de dstBlur y pos
		vec3 offset = (dstColorBlur.rgb - srcColorBlur.rgb);
		gl_FragColor = vec4(srcColor + multiplier*offset, 1.);
	} else {
		gl_FragColor = vec4(0.);
	}
}