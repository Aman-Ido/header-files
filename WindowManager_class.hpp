class WindowManager {
	public:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		std::string window_title = "window-1";
		int width = 640;
		int height = 480;
		
	
	// constructur
	
	// methods
		// method to free everything
		void free_window_manager () {
      std::cout << "\t *** WindowManager::free_window_manager (void) ***" << std::endl;
			if (this -> window != nullptr) {
				SDL_DestroyRenderer (this -> renderer);
				this -> renderer = nullptr;
				SDL_DestroyWindow (this -> window);
				this -> window = nullptr;
				
        
        std::cout << "\t\t * Window, Renderer -> Destroyed -> Cleared" << std::endl;
				// SDL_Quit ();
			}
		}
		
		// create window and renderer
		bool create_window_renderer () {
      std::cout << "\t *** WindowManager::create_window_renderer (void) ***" << std::endl;
			if (SDL_WasInit (0) != 0) { // if the sdl is initialized then we create window and renderer
				// creating window
				this -> window = SDL_CreateWindow (this->window_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED
				, this->width, this->height, SDL_WINDOW_SHOWN);
				if (this -> window == nullptr) {
					std::cerr << "\t\t * Could not create window : " << SDL_GetError() << std::endl;
					return false;
				} else {
					std::cout << "\t\t * Window Created Successfully" << std::endl;
				}
				
				// creating renderer
				this -> renderer = SDL_CreateRenderer (this -> window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				if (this -> renderer == nullptr) {
					std::cerr << "\t\t * SDL_CreateRenderer : " << SDL_GetError() << std::endl;
					return false;
				} else {
					std::cout << "\t\t * Renderer Created Successfully" << std::endl;
				}
			}
			
			return true;
		}
	
	// destructors
	~WindowManager () {
		free_window_manager ();
	}
	
	// getters
	
	// setters
		// set width
		void set_width (int i_width) {
			if (i_width > 0) {
				this -> width = i_width;
			}
		}
		// set height
		void set_height (int i_height) {
			if (i_height> 0) {
				this -> height = i_height;
			}
		}
		// set the window title
		void set_window_title (std::string i_window_title) {
			if (i_window_title != "") {
				this -> window_title = i_window_title;
			}
		}

};
