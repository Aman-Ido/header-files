// class bitmap_font
class Bitmap_Font {
  public:
    SDL_Texture* l_texture;
    int width;
    int height; // height and width of the texture
    bool is_full;
    
    // these are the default values
    int row = 16;
    int col = 16;
    int font_size = 12;
    int col_switch = 0;
    int row_switch = 0;
    
    
    // constructor
    Bitmap_Font ();
    
    // destructor
    ~Bitmap_Font ();
    
    // calling for free texture
    void free_image ();
    
    /* 
      method to load image -> bitmap image, width and height are automatically handled 
    */
    bool load_image (SDL_Renderer* i_renderer, std::string path);
    
    /* 
      method to update format from 16x16 to 16x6
      just input "half" for 16x6
      and anything else (std::string) for 16x16
    */
    void update_format (std::string i_input);
    
    /* 
      method to set up the font size
    */
    void set_font_size (int i_font_size);
    
    /* 
      method to get row
    */
    int get_row (char i_value);
    
    /* 
      method to get col these functions are not necessary for ordinary user
    */
    int get_col (char i_value);
    
    /* 
      method to render text - normal
    */
    void render_text (SDL_Renderer* i_renderer, int x, int y, std::string i_text);
    
    /* 
      method to render the font but advanced
    */
    void render_text_advanced (SDL_Renderer* i_renderer, int x, int y, std::string i_text, bool i_animation);
    
    /* 
      method to change the color
    */
    void change_color (int r, int g, int b);
    
};


/* 
  method to change the color
*/
void Bitmap_Font::change_color (int r, int g, int b) {
  // std::cout << "\t\t * Bitmap_Font::change_color (int, int, int) " << std::endl;
  // std::cout << "\t\t\t -> User should use 'white' or 'grey' image for best results" << std::endl;
  if (this -> l_texture != nullptr) {
    SDL_SetTextureColorMod (this -> l_texture, r, g, b);
  }
}

/*
  void render_text_advanced (SDL_Renderer* i_renderer, int x, int y, std::string i_text, bool i_animation)
  , meaning it will read things like \r \n and put the text acccordingly
  meaning if I type function\r\nfoo, the output will be
  
  --------------
  function
  foo
  --------------
  
  Also I would like to add rotation function as well as animation to it. but they are in their development stage right now
  
*/
void Bitmap_Font::render_text_advanced (SDL_Renderer* i_renderer, int x, int y, std::string i_text, bool i_animation) {
  // only rendering
  
  
  /* 
    looping through text
  */
  for (int i = 0 ; i < i_text.length (); i++) {
    
    // source rect cutting
    SDL_Rect src_rect = {get_col(i_text[i]), get_row(i_text[i]), this -> font_size, this -> font_size}; // cuts out from the source file
    
    // destination rect
    SDL_Rect dest_rect = {0};
    
    /* 
      to check for special character 
    */
    if (i_text[i] == '\n') {
      this -> col_switch ++;
      if (i_text[i - 1] == '\r') {
        this -> row_switch = -1;
      } 
    } 
    if (i_text[i] == '\r') {
      this -> row_switch = 0;  
    } 
    
    /* 
      fill up destination rect
    */
    dest_rect.x = x + (this -> row_switch * this -> font_size); // 10
    dest_rect.y = y + (this -> font_size * this -> col_switch); // 10
    dest_rect.w = this -> font_size;
    dest_rect.h = this -> font_size;
    
  
    // rendering - in future we will probably use SDL_RenderCopyEx
    SDL_RenderCopy (i_renderer, this -> l_texture, &src_rect, &dest_rect);
    this -> row_switch ++;
    
    // this if for animation - just put false for now
    if (i_animation) {
      SDL_RenderPresent (i_renderer);
      SDL_Delay (50);
    }
  }
  
  // resetting 
  this -> row_switch = 0;
  this -> col_switch = 0;
}

/* 
  update the format - to update the format from half (16 x 6 ) or full (16 x 16) 
  * super necessary 
*/
void Bitmap_Font::update_format (std::string i_input) {
  std::cout << "\t * Bitmap_Font::update_format (std::string )" << std::endl;
  if (i_input == "half") {
    this -> is_full = false;
    std::cout << "\t\t * Format updated : HALF" << std::endl;
  } else {
    this -> is_full = true;
    std::cout << "\t\t * Format updated : FULL" << std::endl;
  }
}

// sets the font size 
void Bitmap_Font::set_font_size (int i_font_size) {
  std::cout << "\t * Bitmap_Font::set_font_size (int )" << std::endl;
  if (i_font_size > 0) {
    this -> font_size = i_font_size;
    std::cout << "\t\t * Font Size : " << this -> font_size << std::endl;
  }
}

// methods to get the coordination for row and column -> source image / rect
int Bitmap_Font::get_row (char i_value) {
  if (this -> is_full) {
    
    return floor (i_value / this -> row) * this -> font_size;
  } else {
    return (floor (i_value / this -> row) - 2) * this -> font_size;
  }
}

int Bitmap_Font::get_col (char i_value) {
  return (i_value % this -> col) * this -> font_size;
}

/* 
  render text - function to render the text on the screen 
  it is void and does not print anything on console
*/
void Bitmap_Font::render_text (SDL_Renderer* i_renderer, int x, int y, std::string i_text) {
  // only rendering
  
  // looping through the inputted string
  for (int i = 0 ; i < i_text.length (); i++) {
    
    SDL_Rect src_rect = {get_col(i_text[i]), get_row(i_text[i]), this -> font_size, this -> font_size}; // cuts out from the source file
    /* 
      setting destination rect 
      Note: if you want to zoom in or zoom out on the text just add values to the width and height section of this
      like
      dest_rect.w = this -> font_size + 1; // for magnification (you can do more than 1)
      dest_rect.h = this -> font_size - 1; // for zoom out 
    */
    SDL_Rect dest_rect = {x + (i * this -> font_size), y, this -> font_size, this -> font_size};
    
    // just rendering
    SDL_RenderCopy (i_renderer, this -> l_texture, &src_rect, &dest_rect);
  }
}

/* 
  loading the image -> to load the bitmap image 
  (but you can load any image makes great design patterns) 
  return true - success / false - failure
*/
bool Bitmap_Font::load_image (SDL_Renderer* i_renderer, std::string path) {
  std::cout << "\t * Bitmap_Font::load_image (SDL_Renderer* , std::string )" << std::endl;
  free_image (); // if there were any texture from before
  
  // loading the image as a texture (Must have SDL_image installed and initialized)
  this -> l_texture = IMG_LoadTexture (i_renderer, path.c_str());
  if (this -> l_texture == nullptr) { // error checking
    std::cerr << "\t\t * IMG_LoadTexture () : " << IMG_GetError () << std::endl;
    return false;
  } else {
    std::cout << "\t\t * Image Loaded as Texture : " << path << std::endl;
  }
  
  // querying about the texture to get its width and height
  SDL_QueryTexture (this -> l_texture, nullptr, nullptr, &this -> width, &this -> height);
  
  // returning true if everything is good
  return true;
}

// method to free previously loaded texture image
void Bitmap_Font::free_image () {
  if (this -> l_texture != nullptr ) {
    SDL_DestroyTexture (this -> l_texture);
    this -> l_texture = nullptr;
    this -> width = 0;
    this -> height = 0;
    this -> is_full = false;
  }
}

// constructor
Bitmap_Font::Bitmap_Font () {
  this -> l_texture = nullptr;
  this -> width = 0;
  this -> height = 0;
  this -> is_full = false; // is_full -> true = 16x16 complete ascii 
  // is_full -> false = 16x8 only the necessary ones 
}

// destructor
Bitmap_Font::~Bitmap_Font () {
  free_image ();
}