/* 
  this is a c++ bitmap font class and methods related to that program
*/

// other functions
int m_abs (int value) {
  if (value > 0) {
    return value;
  }
  return -1 * value;
}

// m_update_cursor (source_x, source_y, desti_x, desti_y, cur_x = index (i), cur_y = index (i) <vertical>)
void m_update_cursor (int* src_x, int* src_y, int* dest_x, int* dest_y, int cur_x, int cur_y, char s_value) {
  *src_x = s_value % 16;
  *src_y = s_value / 16;
  
}

// main bitmap font class
class Bitmap_Font {
  public:
    // about the image
    SDL_Texture* image; // default NULL
    int width; // default 0
    int height; // default 0 
    
    /* 
      so that we can adjust the size of the text (without relying on image)
    */
    int zoom; // default 0
    
    int font_size; // default 2
    
    SDL_Color font_color = {0};
    
    int c_font_size;
    
    SDL_Point sw_point; // switch point, x is for horizontal and y is for vertical (for render advanced)
    
    /* 
      values for coordination
    */
    SDL_Rect src = {0}; // for source
    SDL_Rect dest = {0}; // for destination
    
    /* 
      Bitmap_Font - methods
    */
    
    /* 
      structures
    */
    Bitmap_Font (); // sets the values
    ~Bitmap_Font (); // calls free method
    
    /* 
      method to free the loaded image and set the values to their default
    */
    void free_bitmap ();
    
    /* 
      method to load the image
    */
    bool load_bitmap (SDL_Renderer* i_renderer, std::string file_path );
    
    /* 
      method to render the image as per the inputted string
    */
    void render_bitmap (SDL_Renderer* i_renderer, std::string message, int pos_x, int pos_y);
    
    /* 
      method to render the image as per the inputted string, but can also read \n and \r and 
      render as per their meaning
    */
    void render_bitmap_advanced (SDL_Renderer* i_renderer, std::string message, int pos_x, int pos_y, int window_width);
    
    /* 
      method to change the color
    */
    void color_bitmap (int r, int g, int b);
    
    /* 
      method to change the zoom (increase the font size)
    */
    void zoom_bitmap (int value);
    
    
    
    
};

/* 
  constructor
*/
Bitmap_Font::Bitmap_Font () {
  this -> image = nullptr;
  this -> width = 0;
  this -> height = 0;
  
  this -> zoom = 0;
  this -> font_size = 2;
  
  this -> c_font_size = 0;
}

/* 
  destructor
*/
Bitmap_Font::~Bitmap_Font () {
  free_bitmap ();
}

/* 
  method - void free_bitmap (void);
      - destroyes the textures and sets the variable to nullptr
      - reverts the values to their defaults
*/
void Bitmap_Font::free_bitmap () {
  if (this -> image != nullptr) {
    SDL_DestroyTexture (this -> image);
    this -> image = nullptr;
    
    this -> width = 0;
    this -> height = 0;
    
    this -> font_size = 2;
    this -> zoom = 0;
    
    this -> font_color.r = 0;
    this -> font_color.g = 0;
    this -> font_color.b = 0;
    this -> font_color.a = 0;
    
    this -> dest.x = 0;
    this -> dest.y = 0;
    this -> dest.w = 0;
    this -> dest.h = 0;
    
    this -> c_font_size = 0;
    
    this -> src.x = 0;
    this -> src.y = 0;
    this -> src.w = 0;
    this -> src.h = 0;
  }
}

/* 
  method - bool load_bitmap (SDL_Renderer*, std::string file_path);
      - calls free_bitmap () method
      - loads the image as texture
      - sets the width and height value (image's width and height )
      - sets the font_size (image's width / 16)
      
      - returns 'true' on success, 'false' on errors
*/
bool Bitmap_Font::load_bitmap (SDL_Renderer* i_renderer, std::string file_path ) {
  free_bitmap (); // removing previously loaded image
  
  // loading the image texture
  this -> image = IMG_LoadTexture (i_renderer, file_path.c_str());
  
  // error checking
  if (this -> image == nullptr) {
    std::cout << "\t ! Bitmap_Font::load_bitmap () -> image_loading, failed\n\t\t- " << IMG_GetError () << std::endl;
    return false;
  } else {
    std::cout << "\t * Bitmap_Font::load_bitmap () -> image_loading, success\n" << std::endl;
  }
  
  // querying the image
  SDL_QueryTexture (this -> image, nullptr, nullptr, &this -> width, &this -> height);
  
  // setting the font size 
  this -> font_size = this -> width / 16;
  
  // setting width / height of src
  this -> src.w = this -> font_size;
  this -> src.h = this -> font_size;
  
  this -> dest.w = m_abs(this -> font_size + this -> zoom);
  this -> dest.h = m_abs(this -> font_size + this -> zoom);
  
  this -> c_font_size = this -> font_size;
  
  
  return true;
}

/* 
  method - void color_bitmap (int r, int g, int b);
      - this method will only set the values to the SDL Color
*/
void Bitmap_Font::color_bitmap (int r, int g, int b) {
  /* 
    there probably needs to be a value checking before assigning, but later on that 
  */
  
  this -> font_color.r = m_abs (r);
  this -> font_color.g = m_abs (g);
  this -> font_color.b = m_abs (b);
}

/* 
  method - void render_bitmap (SDL_Renderer* i_renderer, std::string message)
*/
void Bitmap_Font::render_bitmap (SDL_Renderer* i_renderer, std::string message, int pos_x, int pos_y) {
  // setting render color
  SDL_SetTextureColorMod (this -> image, this -> font_color.r, this -> font_color.g, this -> font_color.b);
  
  int string_length = static_cast <int> (message.length());
  
  for (int i = 0; i < string_length; i++) {
    // calculating
    this -> src.x = message[i] % 16 * this -> font_size;
    this -> src.y = message[i] / 16 * this -> font_size;
    
    this -> dest.x = pos_x + (i * this -> c_font_size);
    this -> dest.y = pos_y;
    
    // rendering
    SDL_RenderCopy (i_renderer, this -> image, &this -> src, &this -> dest);
  }
  
  
  
}

/* 
  method - zoom_bitmap (int value)
      - this method will only set the value for this -> zoom, and this -> c_font_size (change font size)
      - will also update destination width and height
*/
void Bitmap_Font::zoom_bitmap (int value) {
  this -> zoom = value;
  
  this -> c_font_size = m_abs (this -> font_size + this -> zoom);
  
  this -> dest.w = this -> c_font_size;
  this -> dest.h = this -> c_font_size;
}

/* 
  method - render_bitmap_advanced (SDL_Renderer*, std::string, int, int);
      - sets the color for the text from this -> font_color
      - starts looping the message for characters
      - calculates source positions
      - calcuates the destination positions as per the this -> sw_point (switch point)
      - can read \n \r and if the text is out of Window Width  and render (e.g. inputted_text = "Hello\nWorld!")
                -- Will output --
                * Hello
                * World!
*/
void Bitmap_Font::render_bitmap_advanced (SDL_Renderer* i_renderer, std::string message, int pos_x, int pos_y, int window_width) {
  // changing the color
  SDL_SetTextureColorMod (this -> image, this -> font_color.r, this -> font_color.g, this -> font_color.b);
  
  // looping
  int string_size = static_cast <int> (message.length());
  
  for (int i = 0; i < string_size; i++) {
    // updating positions 
    this -> src.x = (message[i] % 16) * this -> font_size;
    this -> src.y = (message[i] / 16) * this -> font_size;
    
    // calculating the sw_point (switch point)
    /* 
      we will change the y coordinate as per these values \n, \r, for now
    */
    
    if ( (this -> dest.x + this -> dest.w) > window_width ) {
      this -> sw_point.y += 1;
      this -> sw_point.x = 0;
    }
    
    if (message[i] == '\r') {
      
      this -> sw_point.x = 0;
    }
    if (message[i] == '\n') {
      this -> sw_point.y += 1;
      this -> sw_point.x = -1;
    }
    
    this -> dest.x = pos_x + (this -> sw_point.x * this -> c_font_size);
    this -> dest.y = pos_y + (this -> sw_point.y * this -> c_font_size);
    
    // rendering
    SDL_RenderCopy (i_renderer, this -> image, &this -> src, &this -> dest);
    
    // updating switch x
    this -> sw_point.x += 1;
  }
  this -> sw_point.y = 0;
  this -> sw_point.x = 0;
}