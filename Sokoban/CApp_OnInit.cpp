#include "CApp.h"
 
//! An game initialization.
/*!
	The first thing we need to do is start up SDL itself, so we can access its functions. We are telling SDL to Initialize everything it has; there are other parameters you can pass, but understanding them at this point is not important. The next function we use is SDL_SetVideoMode. This bad boy is what creates our window, and our surface. It takes 4 parameters: The width of the window, the height of the window, the bit resolution of the window (recommended to be 16 or 32), and then display flags. There are quite a few display flags, but the ones shown above are fine for now. The first flag tells SDL to use hardware memory for storing our images and such, and the second flag tells SDL to use double buffering (which is important if you don't want flickering on your screen). Another flag that may interest you now is SDL_FULLSCREEN, which makes the window go fullscreen.
*/
bool CApp::OnInit() {

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

	/*!< \brief we have to do a little bit to start SDL_mixer. This is just like starting up SDL, but instead we need to start up SDL_mixer to access sounds. 
	
	Mix_OpenAudio basically Inits SDL_mixer. This function takes 4 arguments. The first is used to specify the frequency, 44100 is usually a good number. But depending on your wav files, you may have to change this. Another common number is 22050. I won't get into detail about frequencies and such, just leave it alone unless you really need to change it. The next is the format, again, it's best to leave it unless you know much about audio (it's basically the size of the samples used, 8bit or 16bit). The next is the number of channels, 1 = mono, 2 = stereo. Note, these channels are different than the other channels I was talking about before. The other channels are "mixing channels," basically streams that I can push audio through. These channels though, are the number of audio outputs. Think of it like the number of speakers that you might have. 2 speakers, 2 channels. The last number is used to set the size of the samples (in bytes). Again, unless you really know what you are doing, it's best to leave these numbers alone. */
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		printf("Failed to initialize AUDIO: %s\n", SDL_GetError());
		return false;
	}
	
	if ((window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL*/)) == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
 
	//Get window surface
    if((Surf_Display = SDL_GetWindowSurface(window)) == NULL) {
		printf("Failed to create our main display Surface! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

	/*! \brief load an image. */
	if((Surf_Test = CSurface::OnLoad("./gfx/yoshi.bmp", Surf_Display)) == NULL) {
		printf("Failed to load an image\n");
        return false;
    }

	CSurface::Transparent(Surf_Test, 255, 0, 255);

	if ((Surf_Grid = CSurface::OnLoad("./gfx/grid.bmp", Surf_Display)) == NULL) {
		return false;
	}

	if ((Surf_X = CSurface::OnLoad("./gfx/x.bmp", Surf_Display)) == NULL) {
		return false;
	}

	if ((Surf_O = CSurface::OnLoad("./gfx/o.bmp", Surf_Display)) == NULL) {
		return false;
	}

	CSurface::Transparent(Surf_X, 255, 0, 255);
	CSurface::Transparent(Surf_O, 255, 0, 255);

	Reset();

	Anim_Yoshi.MaxFrames = 8;	/*!< \brief Now, lets set the MaxFrames. */

	Anim_Yoshi.Oscillate = true;	/*!< \brief If you want to see your animation Oscillate. */

	if (Entity1.OnLoad("./gfx/yoshi.bmp", 64, 64, 8, Surf_Display) == false) {
		return false;
	}

	if (Entity2.OnLoad("./gfx/cat.png", 512, 256, 8, Surf_Display) == false) {
		return false;
	}

	Entity2.X = 100;

	CEntity::EntityList.push_back(&Entity1);
	CEntity::EntityList.push_back(&Entity2);

	if (CArea::AreaControl.OnLoad("./maps/1.area",Surf_Display) == false) {
		printf("Failed to load a map\n");
		return false;
	}

	/*! \brief Initialize players. 
		Simple enough. We set PlayerX, the other Yoshi, over, so that we're not on top of each other initially. */
	if(Player.OnLoad("./gfx/yoshi.png", 64, 64, 8, Surf_Display) == false) {
		return false;
	}
 
	if(Player2.OnLoad("./gfx/yoshi.png", 64, 64, 8, Surf_Display) == false) {
		return false;
	}
 
	Player2.X = 100;
 
	CEntity::EntityList.push_back(&Player);
	CEntity::EntityList.push_back(&Player2);

	CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;	/*!< \brief Remember I said earlier, we're going to make the camera follow our Yoshi. */
	CCamera::CameraControl.SetTarget(&Player.X, &Player.Y);

	/*! \brief load some sounds. */
	if((SoundA = CSoundBank::SoundControl.OnLoad("./sfx/sounda.wav")) == -1) {
		return false;
	}
 
	if((SoundB = CSoundBank::SoundControl.OnLoad("./sfx/soundb.wav")) == -1) {
		return false;
	}

	//	If needed, filter out rpeated events with 

	//SDL_Event event;
	//while (SDL_PollEvent(&event)) {
	//	if (event.type == SDL_QUIT) {
	//		quit = true;
	//	}
	//	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
	//		if (event.key.keysym.sym == SDLK_d)
	//			debug = debug ? false : true;
	//		// ... handle other keys
	//	}
	//}

	//	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
 
    return true;
}
