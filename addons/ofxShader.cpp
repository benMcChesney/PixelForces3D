#include "ofxShader.h"


//char *textFileRead(char *fn);		// some memory allocation happens here
									// be careful...  please don't call load shader 
									// repeatedly !!!!! (you have been warned)

GLchar *LoadShaderText(const char *fileName);

ofxShader::~ofxShader(){
	unload();	
};
//---------------------------------------------------------------
void ofxShader::loadShader(string fragmentName, string vertexName){
	
	fragmentName = ofToDataPath(fragmentName);
	vertexName = ofToDataPath(vertexName);

	
	bLoaded = false;	
	
	if (GLEE_ARB_shader_objects){
		
		// ---------------------------------- (a) load in the shaders
		char *vs = NULL,*fs = NULL;
		vs = LoadShaderText(vertexName.c_str());
		fs = LoadShaderText(fragmentName.c_str());
		
		vertexShader = (GLhandleARB)glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = (GLhandleARB)glCreateShader(GL_FRAGMENT_SHADER);
		
		if( vs == NULL || fs == NULL ){
			printf("unable to load %s \n", vertexName.c_str());
			return;
		}
		
		GLint length = strlen(vs);
		glShaderSourceARB(vertexShader, 1, (const char**)&vs, &length);
		length = strlen(fs);
		glShaderSourceARB(fragmentShader, 1, (const char**)&fs, &length);
		
		char infobuffer[1000];
		GLsizei infobufferlen = 0;
		
		// ----------------------------------- (b) compile the shaders
		// try to compile "vertex shader"
		glCompileShaderARB(vertexShader);
		
		//please add compile status check in:
		GLint compileStatus = 0;
		glGetObjectParameterivARB( vertexShader, GL_COMPILE_STATUS, &compileStatus );
		printf("vertexShader status = %i \n", compileStatus);
		
		
		glGetInfoLogARB(vertexShader, 999, &infobufferlen, infobuffer);
		if (infobufferlen != 0){
			infobuffer[infobufferlen] = 0;
			printf("vertexShader reports: %s \n", infobuffer);
			return;
		}
		
		// ------------------------------------
		// try to compile "fragment shader"
		glCompileShaderARB(fragmentShader);
		
		

		glGetObjectParameterivARB( fragmentShader, GL_COMPILE_STATUS, &compileStatus );
		printf("fragmentShader status %i \n", compileStatus);
		
		
		glGetInfoLogARB(fragmentShader, 999, &infobufferlen, infobuffer);
		if (infobufferlen != 0){
			infobuffer[infobufferlen] = 0;
			printf("fragmentShader reports: %s \n", infobuffer);
			return;
		}
		
		// ----------------------------------- (c) link the shaders
		shader = glCreateProgramObjectARB();
		glAttachObjectARB(shader,vertexShader);
		glAttachObjectARB(shader,fragmentShader);
		glLinkProgramARB(shader);
		
		
		bLoaded = true;
			
	} else {
	
		printf("sorry, it looks like you can't run 'ARB_shader_objects' \n please check the capabilites of your graphics card (http://www.ozone3d.net/gpu_caps_viewer/) \n");
	
	}


}
		
//---------------------------------------------------------------
void ofxShader::loadShader(string shaderName){
	bLoaded = false;
	string fragmentName = shaderName + ".frag";
	string vertexName   = shaderName + ".vert";
	loadShader(fragmentName, vertexName);
}



//---------------------------------------------------------------
void ofxShader::unload(){
	
	if (vertexShader){
		glDetachObjectARB(shader,vertexShader);
		glDeleteObjectARB(vertexShader);
		vertexShader = NULL;
	}
	
	if (fragmentShader){
		glDetachObjectARB(shader,fragmentShader);
		glDeleteObjectARB(fragmentShader);
		fragmentShader = NULL;
	}
	
	if (shader){
		glDeleteObjectARB(shader);
		shader = NULL;
	}
	
}

//---------------------------------------------------------------

void ofxShader::setShaderActive(bool bActive){
	if (GLEE_ARB_shader_objects && bLoaded == true){
		if (bActive == true){
			glUseProgramObjectARB(shader);
		} else {
			glUseProgramObjectARB(0);
		}
	}

}

//---------------------------------------------------------------
void ofxShader::setUniformVariable1f (char * name, float value){
	if (bLoaded == true){
		glUniform1fARB(glGetUniformLocationARB(shader, name), value);
	}
}
void ofxShader::setUniformVariable1i (char * name, int value){
	if (bLoaded == true){
		glUniform1iARB(glGetUniformLocationARB(shader, name), value);
	}
}
void ofxShader::setUniformVariable1fv (char * name, int count, float * value){
	if (bLoaded == true){
		glUniform1fvARB(glGetUniformLocationARB(shader, name), count, value);
	}
}
void ofxShader::setUniformVariable3fv (char * name, int count, float * value){
	if (bLoaded == true){
		glUniform3fvARB(glGetUniformLocationARB(shader, name), count, value);
	}
}
void ofxShader::setUniformVariable4fv (char * name, int count, float * value){
	if (bLoaded == true){
		glUniform4fvARB(glGetUniformLocationARB(shader, name), count, value);
	}
}
void ofxShader::setUniformVariable2f (char * name, float value, float value2){
	if (bLoaded == true){
		glUniform2fARB(glGetUniformLocationARB(shader, name), value, value2);
	}
}
void ofxShader::setUniformVariable3f (char * name, float value, float value2, float value3){
	if (bLoaded == true){
		glUniform3fARB(glGetUniformLocationARB(shader, name), value, value2, value3);
	}
}

//---------------------------------------------------------
// below is from: www.lighthouse3d.com
// you may use these functions freely. they are provided as is, and no warranties, either implicit, or explicit are given
//---------------------------------------------------------
/*
char *textFileRead(char *fn) {

	FILE *fp;
	char *content 	= 	NULL;
	int count		=	0;

	if (fn != NULL) {
		fp = fopen(fn,"rt");
		if (fp != NULL) {
		
		      
      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
      fseek(fp, 0, SEEK_SET);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	
	return content;
}*/

GLchar *LoadShaderText(const char *fileName)
{
    GLchar *shaderText = NULL;
    GLint shaderLength = 0;
    FILE *fp;

    fp = fopen(fileName, "r");
    if (fp != NULL)
    {
        while (fgetc(fp) != EOF)
        {
            shaderLength++;
        }
        rewind(fp);
        shaderText = (GLchar *)malloc(shaderLength+1);
        if (shaderText != NULL)
        {
            fread(shaderText, 1, shaderLength, fp);
        }
        shaderText[shaderLength] = '\0';
        fclose(fp);
    }

    return shaderText;
}
