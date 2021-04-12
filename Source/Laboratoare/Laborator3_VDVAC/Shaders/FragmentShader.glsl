#version 430
layout(location = 0) out vec4 out_color;

uniform sampler2D textura1;


layout(location = 0) in vec2 tex_coord;

void main(){


	vec3 tex1 = texture(textura1, tex_coord).xyz;
	
	//canalul alfa - construit in functie de intensitatea din textura
	float alpha = tex1.x * 0.1;
	out_color = vec4(tex1* alpha, alpha);
}