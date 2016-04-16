#include "MainMenu.h"

const int TEXTURE_COUNT=1;
static GLuint texName[TEXTURE_COUNT];

//The music that will be played
Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gSaber = NULL;

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    //Load music
    string s =  GlobalClass::instance()->get_path();
    char  rutaMusic[300];
    sprintf(rutaMusic,"%s%s", s.c_str() , "sounds/starwars.wav");
    // cout << rutaMusic << endl;
    gMusic = Mix_LoadMUS( rutaMusic );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    //Load sound effects
    char  rutaSaber[300];
    sprintf(rutaSaber,"%s%s", s.c_str() , "sounds/light-saber-on.wav");
    // cout << rutaSaber << endl;
    gSaber = Mix_LoadWAV( rutaSaber );
    if( gSaber == NULL )
    {
        printf( "Failed to load gSaber sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    //Load sound effects
    char  rutaScratch[300];
    sprintf(rutaScratch,"%s%s", s.c_str() , "sounds/scratch.wav");
    // cout << rutaSaber << endl;
    gScratch = Mix_LoadWAV( rutaScratch );
    if( gScratch == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    return success;
}


//Makes the image into a texture, and returns the id of the texture
void loadTexture(Image* image,int k)
{

    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    //Filtros de ampliacion y redución con cálculo mas cercano no es tan bueno pero es rápido
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    
    //Filtros de ampliacion y redución con cálculo lineal es mejo pero son más calculos
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
}
void initRendering()
{
    //Declaración del objeto Image
    Image* image;
    GLuint i=0;
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(TEXTURE_COUNT, texName); //Make room for our texture
    
    string s =  GlobalClass::instance()->get_path();

    // cout << s << endl;

    char  ruta[300];
    sprintf(ruta,"%s%s", s.c_str() , "images/AventuraWallpaper.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    
    
    delete image;
}


MainMenu::MainMenu(int w, int h){

    initRendering();
    loadMedia();

    glClearColor(.9, .9, .9, 1);
    
    //getParentPath();
    
    this->reshape(w,h);
    state = 0;
    cout << "MainMenu" << endl;
    

    
    
}

void MainMenu::timer(int v){

}

void MainMenu::display(){

    //glClearColor(1.0,1.0,1.0,1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    ///*

    float minCoord = -50.0f;
    float maxCoord = 50.0f;
    
    //Habilitar el uso de texturas
    glEnable(GL_TEXTURE_2D);
    
    //Elegir la textura del Quads: angulo cambia con el timer
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    
    glBegin(GL_QUADS);
    //Asignar la coordenada de textura 0,0 al vertice
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(minCoord, minCoord, 0);
    //Asignar la coordenada de textura 1,0 al vertice
    glTexCoord2f(1.0f, 0.0f); ///-
    glVertex3f(maxCoord, minCoord, 0);
    //Asignar la coordenada de textura 1,1 al vertice
    glTexCoord2f(1.0f,1.0f); //-
    //glTexCoord2f(1.0f,1.0f);
    //glTexCoord2f(2.0f,5.0f);
    glVertex3f(maxCoord, maxCoord, 0);
    //Asignar la coordenada de textura 0,1 al vertice
    glTexCoord2f(0.0f, 1.0f);
    //glTexCoord2f(0.0f, 5.0f);
    
    glVertex3f(minCoord, maxCoord, 0);
    glEnd();
    
    //*/
    
	//glRectd(-30, -30, 30, 30);

    glutSwapBuffers();
}

void MainMenu::reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-50, 50, -50, 50);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MainMenu::keyboard(unsigned char key, int, int){
    switch(key) {
        case 'I':
        case 'i':
        state = 1;
        break;
        case 'M':
        case 'm':
         //If there is no music playing
        if( Mix_PlayingMusic() == 0 )
        {
            //Play the music
            cout << "music" << endl;
            Mix_PlayMusic( gMusic, -1 );
        }
        //If music is being played
        else
        {
        //If the music is paused
            if( Mix_PausedMusic() == 1 )
            {
                //Resume the music
                cout << "resume" << endl;
                Mix_ResumeMusic();
            }
            //If the music is playing
            else
            {
                cout << "pause" << endl;
                //Pause the music
                Mix_PauseMusic();
            }
        }
        break;
        case 'S':
        case 's':
        cout << "Stop" << endl;
        //Stop the music
        Mix_HaltMusic();
        break;
        //Play scratch sound effect
        case 'X':
        case 'x':
        cout << "scratch" << endl;
        Mix_PlayChannel( 0, gScratch, 0 );
        break;
        case 'Z':
        case 'z':
        cout << "scratch" << endl;
        Mix_PlayChannel( 1, gSaber, 0 );
        break;
    }
}

void MainMenu::EventLoop(int){

}

void close()
{


    // //Free the sound effects
    // Mix_FreeChunk( gScratch );
    // Mix_FreeChunk( gHigh );
    // Mix_FreeChunk( gMedium );
    // Mix_FreeChunk( gLow );
    // gScratch = NULL;
    // gHigh = NULL;
    // gMedium = NULL;
    // gLow = NULL;

    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
}