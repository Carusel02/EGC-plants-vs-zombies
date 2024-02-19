#pragma once
#pragma comment(lib, "winmm.lib")

#include "components/simple_scene.h"

#include <Windows.h>
#include <mmsystem.h>


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        struct infoTurret {
            glm::vec3 position;
            glm::vec2 margin1;
            glm::vec2 margin2;
            glm::vec3 color;
            bool click;
            std::string meshID;
            int colorID;

            infoTurret(const glm::vec3& pos, const glm::vec2& m1, const glm::vec2& m2, const glm::vec3& col, bool clk, const std::string& meshId, int cl)
                : position(pos), margin1(m1), margin2(m2), color(col), click(clk), meshID(meshId), colorID(cl) {
            }

            infoTurret() {
                // Default constructor, initializes members to default values
                position = glm::vec3(0.0f, 0.0f, 0.0f);
                margin1 = glm::vec2(0.0f, 0.0f);
                margin2 = glm::vec2(0.0f, 0.0f);
                color = glm::vec3(0.0f, 0.0f, 0.0f);
                click = false;
                meshID = "";
                colorID = 0;
            }

            infoTurret(int type) {
                switch (type) {
                case 1: {
                    position = glm::vec3(0.0f, 0.0f, 0);
                    margin1 = glm::vec2(0.0f, 0.0f);
                    margin2 = glm::vec2(0.0f, 0.0f);
                    color = glm::vec3(0.90f, 0.60f, 0.36f);
                    click = false;
                    meshID = "";
                    colorID = 0;
                    }
                    break;
                case 2: {
                    position = glm::vec3(0.0f, 0.0f, 0);
                    margin1 = glm::vec2(0.0f, 0.0f);
                    margin2 = glm::vec2(0.0f, 0.0f);
                    color = glm::vec3(0.36f, 0.82f, 0.93f);
                    click = false;
                    meshID = "";
                    colorID = 0;
                    }
                    break;
                case 3: {
                    position = glm::vec3(0.0f, 0.0f, 0);
                    margin1 = glm::vec2(0.0f, 0.0f);
                    margin2 = glm::vec2(0.0f, 0.0f);
                    color = glm::vec3(0.60f, 0.56f, 0.87f);
                    click = false;
                    meshID = "";
                    colorID = 0;
                }
                    break;
                case 4: {
                    position = glm::vec3(0.0f, 0.0f, 0);
                    margin1 = glm::vec2(0.0f, 0.0f);
                    margin2 = glm::vec2(0.0f, 0.0f);
                    color = glm::vec3(0.99f, 0.93f, 0.56f);
                    click = false;
                    meshID = "";
                    colorID = 0;
                }
                    break;
                default: {
                    position = glm::vec3(0.0f, 0.0f, 0);
                    margin1 = glm::vec2(0.0f, 0.0f);
                    margin2 = glm::vec2(0.0f, 0.0f);
                    color = glm::vec3(0.0f, 0.0f, 0.0f);
                    click = false;
                    meshID = "";
                    colorID = 0;
                }
                    break;
                }
            }

            void SetMeshID(const std::string& value) {
                meshID = value;
            }

            // check star cost
            bool checkStarCost(int starCount) {
                const int prices[] = { 1, 2, 2, 3 };
                int price = (colorID >= 0 && colorID < sizeof(prices) / sizeof(prices[0])) ? prices[colorID] : -1;
                return (price <= starCount);
               
            }

        };


        struct infoSquare {
            glm::vec3 position;
            glm::vec2 margin1;
            glm::vec2 margin2;
            bool place;
            float time;
            int squareID;
            bool shoot;
            int color;
            int line;
            int col;
            bool makeDeleteAnimation;
            Mesh* mesh;

            infoSquare(const glm::vec3& pos, const glm::vec2& m1, const glm::vec2& m2, bool f, float tmp, int id, bool sh, int cl, int ln, int colu, bool mda, Mesh *object)
                : position(pos), margin1(m1), margin2(m2), place(f), time(tmp), squareID(id), shoot(sh), color(cl), line(ln), col(colu),
                makeDeleteAnimation(mda), mesh(object) {
			}
            
            infoSquare() {
				position = glm::vec3(0.0f, 0.0f, 0.0f);
				margin1 = glm::vec2(0.0f, 0.0f);
				margin2 = glm::vec2(0.0f, 0.0f);
                place = false;
                time = 0.0f;
				squareID = 0;
                shoot = false;
                color = -1;
                line = -1;
                col = -1;
                makeDeleteAnimation = false;
                mesh = NULL;
			}
            
        };

        struct infoEnemy {
            glm::vec3 position;
            int health;
            float speed;
            int enemyID;
            float moveTime;
            int color;
            int line;
            bool deleteEnemy;
            bool scaleAnimation;
            float scaleTime;
            bool deleteHealth;
            bool singleCheck;

            infoEnemy(const glm::vec3& pos, int hp, float sp, int enID, float mvT, int cl, int ln, bool delEn, bool an, float sT, bool dH, bool sgck)
                : position(pos), health(hp), speed(sp), enemyID(enID), moveTime(mvT), color(cl), line(ln), deleteEnemy(delEn), scaleAnimation(an), scaleTime(sT), deleteHealth(dH),
                singleCheck(sgck) {
			}

        };

        struct infoLine {
            
            int colorHere[4][4];

            infoLine() {
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
						colorHere[i][j] = 0;
					}
				}
			}

        };

        struct infoProjectile {
            glm::vec3 position;
            float dimension;
			int color;
            float moveTime;
            int projectileID;
            int line;

            infoProjectile(const glm::vec3& pos, float dim, int cl, float mvT, int ID, int ln)
				: position(pos), dimension(dim), color(cl), moveTime(mvT), projectileID(ID), line(ln) {}


        };

        struct infoStar {
            glm::vec3 position;
            float dimension; // dimension/2 ~ radius
            int color;
            int starID;
            bool deleteStar;

            infoStar(const glm::vec3& pos, float dim, int cl, int ID, bool delSt)
				: position(pos), dimension(dim), color(cl), starID(ID), deleteStar(delSt) {}

            bool checkCircle(float xp, float yp) {
                // Calculate the distance between the point and the center of the circle
                float distance = sqrt((xp - position.x) * (xp - position.x) + (yp - position.y) * (yp - position.y));

                // Check if the distance is less than the radius
                return distance <= dimension/2;
            }

        };

        struct infoStarBar {
            glm::vec3 position;
            float dim;
            int starbarID;

            infoStarBar(const glm::vec3& pos, float dimension, int ID)
                : position(pos), dim(dimension), starbarID(ID) {
            }
        };

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void AddMeshToListPerma(Mesh* mesh);
        void AddMeshToListDynamic(Mesh* mesh);
        void AddMeshToListEnemy(Mesh* mesh);
        void AddMeshToListProjectile(Mesh* mesh);
        void AddMeshToListStars(Mesh* mesh);
        void AddMeshToListBarStars(Mesh* mesh);
        void AddMeshToListBarHealth(Mesh* mesh);
        void RenderStars();

        void RenderScene();
        void DragAndDrop();
        void PlaceTurret(float deltaTimeSeconds);
        int  AddSquareTurret(infoTurret turret);
        int  DeleteSquareTurret();
        void CheckTurretTime();
        void EnemyAnimation(float deltaTimeSeconds);
        int RandomNumber(int min, int max);
        void ShootAnimation(float deltaTimeSeconds);
        void CheckShootAnimation();
        void RenderProjectile(float deltaTimeSeconds);
        void ColisionEnemyProjectile();
        void ColisionEnemyTurret();
        void GenerateStars(float deltaTimeSeconds);
        void RenderStarsBar();
        void RenderHealthBar();

     protected:

         int startX;
         int startY;
        
         std::unordered_map<std::string, Mesh*> meshesPerma;
         std::unordered_map<std::string, Mesh*> meshesDynamic;
         std::unordered_map<std::string, Mesh*> meshesEnemy;
         std::unordered_map<std::string, Mesh*> meshesProjectile;
         std::unordered_map<std::string, Mesh*> meshesStars;
         std::unordered_map<std::string, Mesh*> meshesBarStars;
         std::unordered_map<std::string, Mesh*> meshesBarHealth;
         

         float time;
         float generationTime;
         float generationStarsTime;
         float delayTime;
         float debugTime;
         int enemyID;
         int projectileID;
         int starsID;
         int starCount = 0;
         int healthCount = 3;

         
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        float heartSize;
        float squareSize;

        std::vector<infoTurret> turretInfoVector;
        std::vector<infoSquare> squareInfoVector;
        std::vector<infoEnemy> enemyInfoVector;
        std::vector<infoProjectile> projectileInfoVector;
        std::vector<infoStar> starsInfoVector;
        std::vector<infoStarBar> starBarInfoVector;

        glm::vec3 colors[4] = { glm::vec3(0.90f, 0.60f, 0.36f) , glm::vec3(0.36f, 0.82f, 0.93f) , glm::vec3(0.60f, 0.56f, 0.87f) , glm::vec3(0.99f, 0.93f, 0.56f) };
        glm::vec3 second_colors[4] = {};
        infoLine line;

        int scale = 2;

        float final_scale = 1;
        
        float increase_difficulty = 8.0f;
        float speed_difficulty = 50.0f;

    };
}   // namespace m1