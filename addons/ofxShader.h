#ifndef _OFX_SHADER
#define _OFX_SHADER


#include "ofMain.h"



//		---------------------------------------
// 		very useful info here:
// 		http://www.evl.uic.edu/aej/594/



/*
 // how to get "compiled" ok then use it:
 
 GLint compileStatus;
 glGetObjectParameterivARB( shader, GL_COMPILE_STATUS, &compileStatus );
 glGetObjectParameterivARB( program, GL_INFO_LOG_LENGTH, &infoLogLen );
 infoLog = new GLchar[infoLogLen+1];
 glGetProgramInfoLogARB(program, infoLogLen, NULL, infoLog );
 infoLog[infoLogLen] = '\0';
 fprintf( stderr, "Info Log:\n%s\n", infoLog );	
 
 */

class ofxShader{
	
public:
	
	ofxShader(){};
	~ofxShader();
	void 	loadShader(string shaderName);	
	void 	loadShader(string fragmentShaderName, string vertexShaderName);	
	
	void 	unload();
	void 	setShaderActive(bool bActive);
	void 	setUniformVariable1f (char * name, float value);
	void 	setUniformVariable1i (char * name, int value);
	void 	setUniformVariable2f (char * name, float value, float value2);
	void 	setUniformVariable3f (char * name, float value, float value2, float value3);
	void    setUniformVariable1fv (char * name, int count, float * value);
	void    setUniformVariable3fv (char * name, int count, float * value);
	void    setUniformVariable4fv (char * name, int count, float * value);
	
	GLhandleARB 	vertexShader;
	GLhandleARB 	fragmentShader;
	GLhandleARB 	shader;
	
	bool			bLoaded;
};

#endif	

