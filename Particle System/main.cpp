#include "raylib.h"
#include<vector>
#include<string>
#include<bits/stdc++.h> 


#define MAX_PARTICLES 400

using namespace std;


Vector2 operator + (Vector2 const &v1, Vector2 const &v2) { 
    Vector2 v{v1.x + v2.x, v1.y + v2.y}; 
    return v;
} 

class Particle final{
    public:
        Vector2 acc{0.0f, 0.05f};
        Vector2 position;
        Vector2 velocity{ (float)GetRandomValue(-20, 20)*.1f, (float)GetRandomValue(-50, -20)*.1f };
        float size{5.0f};
        
        Particle(Vector2& pos)
            :position{pos}  
        {
        }
        
        void draw(){
            // DrawCircle(position.x, position.y, size, RED);
			      DrawRectangle(position.x, position.y, size, size, ORANGE);
            // DrawCircleLines(position.x, position.y, size, RAYWHITE);
        }
        void update(){
            velocity = velocity + acc;
            position = position + velocity;
            if (GetRandomValue(0, 100)<30) size -= 1;
        }
};

class System final{
    public:
        vector<Particle> system;
		
		
        
        System(Vector2& pos) noexcept {
			  system.reserve(MAX_PARTICLES);
            for (int i = 0; i < MAX_PARTICLES; i++) { 
                system.emplace_back(pos);
            }
        }

		
        void draw(){
            for (vector<Particle>::iterator obj = system.begin(); obj < system.end(); obj++) {
                (*obj).draw();
            }

        }
        
        void update(){
            system.erase( 
                std::remove_if( system.begin(), system.end(), []( auto& p ){ 
                   p.update(); return p.size <= 0; 
                } ), 
                system.end() 
            );

        }
};


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Particle System");
 
    SetTargetFPS(60);
    vector<System> P_system;
    Vector2 m_pos;
    //--------------------------------------------------------------------------------------
	
	P_system.reserve(50);
	
    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            m_pos = (Vector2){(float)GetRandomValue((GetMousePosition().x-20)*10, (GetMousePosition().x+20)*10)*.1f, (float)GetMousePosition().y};
            P_system.emplace_back(m_pos);
        }

        	
		//Write FPS
        // int fps = GetFPS();
        // std::string str = std::to_string(fps);
        // std::string thestring = "FPS:"+str;
        // char const *newstr = thestring.c_str();
    //FPS ; Uncomment this part to see the fps
		
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
			P_system.erase( 
                std::remove_if( P_system.begin(), P_system.end(), []( System& sys ){ 
                   sys.update(); 
				   sys.draw(); 
				   return sys.system.size() <= 0; 
                } ), 
                P_system.end() 
            );
            // DrawText(newstr, 10, 10, 20, MAROON); //To draw string ie the fps
		
            
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
