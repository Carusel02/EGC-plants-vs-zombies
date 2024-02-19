#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <random>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

// add meshes to meshes map
void Tema1::AddMeshToListPerma(Mesh* mesh)
{
    if (mesh->GetMeshID())
    {
        meshesPerma[mesh->GetMeshID()] = mesh;
    }
}

void Tema1::AddMeshToListDynamic(Mesh* mesh)
{
    if (mesh->GetMeshID())
    {
        meshesDynamic[mesh->GetMeshID()] = mesh;
    }
}

void Tema1::AddMeshToListEnemy(Mesh* mesh)
{
    if (mesh->GetMeshID())
    {
        meshesEnemy[mesh->GetMeshID()] = mesh;
    }
}

void Tema1::AddMeshToListProjectile(Mesh* mesh)
{
    if (mesh->GetMeshID())
    {
        meshesProjectile[mesh->GetMeshID()] = mesh;
    }
}

void Tema1::AddMeshToListStars(Mesh* mesh)
{
    if (mesh->GetMeshID())
    {
        meshesStars[mesh->GetMeshID()] = mesh;
    }
}

void Tema1::AddMeshToListBarStars(Mesh* mesh)
{
    if (mesh->GetMeshID())
    {
        meshesBarStars[mesh->GetMeshID()] = mesh;
    }
}

void Tema1::AddMeshToListBarHealth(Mesh* mesh)
{
    if (mesh->GetMeshID())
    {
		meshesBarHealth[mesh->GetMeshID()] = mesh;
	}
}

// add a turret to a square

int Tema1::AddSquareTurret(infoTurret turretTarget) {
	
    glm::vec2 cursor = window->GetCursorPosition();

    for (int i = 0; i < 9; i++) {
        
        if (cursor.x >= squareInfoVector[i].margin1.x && cursor.x <= squareInfoVector[i].margin2.x &&
            720 - cursor.y >= squareInfoVector[i].margin1.y && 720 - cursor.y <= squareInfoVector[i].margin2.y) {
            if (squareInfoVector[i].place == false && turretTarget.checkStarCost(starCount)) {
				squareInfoVector[i].place = true;
                squareInfoVector[i].time = time;
                squareInfoVector[i].color = turretTarget.colorID;

                if (turretTarget.colorID == 0)
                    starCount--;
                if (turretTarget.colorID == 1)
                    starCount -= 2;
                if (turretTarget.colorID == 2)
                    starCount -= 2;
                if (turretTarget.colorID == 3)
                    starCount -= 3;


                // render in front of green square
                glm::vec3 position = glm::vec3(squareInfoVector[i].position.x - 20, squareInfoVector[i].position.y, 1);
				Mesh* turret = object2D::CreateTurret("turret" + std::to_string(squareInfoVector[i].squareID), position, squareSize * 0.7, turretTarget.color, true);
				AddMeshToListDynamic(turret);
				
				
			}
            return squareInfoVector[i].squareID;
		}
    }

    return 0;
}

// check colision between enemy and turret

void Tema1::ColisionEnemyTurret() {

    // for every enemy
    for (auto enemy = enemyInfoVector.begin(); enemy != enemyInfoVector.end(); ++enemy) {
        // for every turret
        for (auto turret = squareInfoVector.begin(); turret != squareInfoVector.end(); ++turret) {
            
            if (enemy->line - 1 == turret->line && turret->place == true) {
                if (abs(enemy->position.x - (turret->margin1.x + turret->margin2.x) / 2) < (50 + 40)) {
                    

                    // cout << "squareID " << turret->squareID << endl;
                    // just once
                    enemy->singleCheck = true;
                    
                    
                    // clear relevant info
                    
                    turret->place = false;
                    turret->color = -1;
                    turret->shoot = false;

                    // make a scale, then delete mesh
                    turret->makeDeleteAnimation= true;
                    turret->mesh = meshesDynamic["turret" + std::to_string(turret->squareID)];
                    meshesDynamic.erase("turret" + std::to_string(turret->squareID));
                }
			}

		}
	}
}

int Tema1::DeleteSquareTurret() {

    glm::vec2 cursor = window->GetCursorPosition();

    for (int i = 0; i < 9; i++) {

        if (cursor.x >= squareInfoVector[i].margin1.x && cursor.x <= squareInfoVector[i].margin2.x &&
            720 - cursor.y >= squareInfoVector[i].margin1.y && 720 - cursor.y <= squareInfoVector[i].margin2.y) {
            if (squareInfoVector[i].place == true) {
                
                // clear relevant info
                squareInfoVector[i].place = false;
                squareInfoVector[i].color = -1;
                squareInfoVector[i].shoot = false;
                
                // delete mesh on square
                meshesDynamic.erase("turret" + std::to_string(squareInfoVector[i].squareID));


            }
            return squareInfoVector[i].squareID;
        }
    }

    return 0;
}

void Tema1::CheckTurretTime() {
    
    // turret time is set on square time
    for (int i = 0; i < 9; i++) {
        if (squareInfoVector[i].place == true) {
            if (time - squareInfoVector[i].time >= 5) {
				squareInfoVector[i].place = false;
				meshesDynamic.erase("turret" + std::to_string(squareInfoVector[i].squareID));
			}
		}
    }
    


}

int Tema1::RandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    cout << "Resolution X : " << resolution.x << endl;
    cout << "Resolution Y : " << resolution.y << endl;
    int startX = 110;
    int startY = 640;

    time = 0;
    generationTime = 0;
    generationStarsTime = 0;
    delayTime = 0;
    debugTime = 0;
    enemyID = 0;
    projectileID = 0;
    starsID = 0;

    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    

    float squareSide = 120;
    float turretSide = 100;
    float heartSide = 80;
    squareSize = squareSide;

    // Initialize heart size
    heartSize = 50;



    // set default values for turrets
    int startPositionX = startX;
    int startPositionY = startY;

    // set margin values for turrets !! COINCIDA CU PATRAT ALB
    int marginStartX1 = 70;
    int marginStartY1 = 580; 

    int marginStartX2 = marginStartX1 + squareSize;
    int marginStartY2 = marginStartY1 + squareSize;

    // init space between objects
    int space = 30;

    // 0. BONUS BAR STARS


    for (int i = 0; i < 12; i++) {

        infoStarBar star(glm::vec3(680 + i * 50, 600, 1), 50, i);
        starBarInfoVector.push_back(star);
        Mesh* starBarMesh = object2D::CreateStar("star_bar" + std::to_string(i + 1), starBarInfoVector[i].position, star.dim, glm::vec3(1, 1, 1), true);
        AddMeshToListBarStars(starBarMesh);
    }

    // CREATE MESHES

    // 1. GENERAL TURRETS 

    for (int i = 0; i < 4; i++) {
        infoTurret turret(glm::vec3(startPositionX, startPositionY, 0), glm::vec2(marginStartX1, marginStartY1), glm::vec2(marginStartX2, marginStartY2), colors[i],
            false, "turret" + std::to_string(i + 1), i);
        startPositionX += squareSize + space;
        marginStartX1 += squareSize + space;
        marginStartX2 += squareSize + space;
        turretInfoVector.push_back(turret);
    }

     
    // PERMA TURRETS
    {
        for (int i = 0; i < 4; i++) {
            // formula for x position = x.start + i * (spaces + squareSide)
            Mesh* turret = object2D::CreateTurret(turretInfoVector[i].meshID, turretInfoVector[i].position, squareSide * 0.7, turretInfoVector[i].color, true);
            AddMeshToList(turret);
            AddMeshToListPerma(turret);
        }

    }

    // 2. WHITE SQUARES

    {   // same as marginStartX1 and marginStartY1
        int positionX = startX + 20;
        int positionY = startY;

        for (int i = 0; i < 4; i++) {
            // formula = x + i * (space + squareSize)
            glm::vec3 position = glm::vec3(positionX + i * (space + squareSize), positionY, 0);
            Mesh* white_square = object2D::CreateSquare("white_square" + std::to_string(i + 1), position, squareSide, glm::vec3(1, 1, 1), false);
            AddMeshToList(white_square);
            AddMeshToListPerma(white_square);
        }
    }


    //  3. GREEN SQUARES
    for (int i = 0; i < 9; i++) {
        int row = i / 3;
        int col = i % 3;

        
        float posX = (startX + 20) + col * (squareSide + space);
        float posY = (20 + squareSize/2) + row * (squareSide + space);

        glm::vec3 position(posX, posY, -1);
        glm::vec2 margin1(posX - squareSize/2, posY - squareSize/2);
        glm::vec2 margin2(posX + squareSize/2, posY + squareSize/2);

        int squareID = i + 1;
        bool full = false;

        infoSquare square(position, margin1, margin2, full, time, squareID, false, -1, row, col, false, NULL);
        squareInfoVector.push_back(square);
    }
    
    
    
    {

        for (int i = 0; i < 9; i++) {
            Mesh* green_square = object2D::CreateSquare("green_square" + std::to_string(squareInfoVector[i].squareID), squareInfoVector[i].position, squareSide, glm::vec3(0.40f, 0.96f, 0.50f), true);
            AddMeshToList(green_square);
            AddMeshToListPerma(green_square);
        }
    }



    // create 3 hearts
    {   // |           * * * |
        // |                 |
        // |                 |
        // |                 |

        int positionX = 1000;
        int positionY = 650;
        int spaces = 30;

        for (int i = 0; i < 3; i++) {
            glm::vec3 position = glm::vec3(positionX + i * (spaces + heartSize), positionY, 0);
            Mesh* heart = object2D::CreateHeart("heart" + std::to_string(i + 1), position, heartSize, heartSize, glm::vec3(0.75f, 0, 0), true);
            AddMeshToListBarHealth(heart);

            
            // AddMeshToList(heart);
        }

    }

    // create cost stars
    {   
        int positionX = 130;
        int positionY = 550;
        int space = 0;
        for (int i = 0; i < 8; i++) {
            if (i == 1)
                positionX += 90;
            if (i == 3)
                positionX += 70;
            if(i == 5)
                positionX += 50;
            glm::vec3 position = glm::vec3(positionX + i * 40 , positionY, 0);
			Mesh* star = object2D::CreateStar("star" + std::to_string(i + 1), position, 30, glm::vec3(1, 1, 1), true);
			AddMeshToListPerma(star);
		}

    }

    // create rectangle
    Mesh* rectangle = object2D::CreateRegtangle("rectangle", glm::vec3(10, 20, 0), 40, 420, glm::vec3(0.9f, 0, 0), true);
    AddMeshToListPerma(rectangle);

    for(int i = 0 ; i < 9 ; i++)
		cout << "Square " << i + 1 << " : " << squareInfoVector[i].margin1.x << " " << squareInfoVector[i].margin1.y << " " << squareInfoVector[i].margin2.x << " " << squareInfoVector[i].margin2.y << endl;


}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.18f, 0.20f, 0.22f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::RenderScene() {
    
    // safe set
    modelMatrix = glm::mat3(1);
    // render all objects in meshesPerma
    for (const auto& meshPair : meshesPerma) {
        RenderMesh2D(meshPair.second, shaders["VertexColor"], modelMatrix);
    }


}

void Tema1::DragAndDrop() {

    glm::vec2 cursor = window->GetCursorPosition();
    
    // turrets

    for (int i = 0; i < 4; i++) {
        if (turretInfoVector[i].click) {
            // cout << "MOUSE CLICK IMPORTANT!! " << cursor.x << " " << 720 - cursor.y << endl;
            // int currentPosition = turretA.position.x - cursor.x;
            // int currentPosition2 = turretA.position.y - cursor.y;
            // modelMatrix *= transform2D::Translate(currentPosition, currentPosition2);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(cursor.x, 720 - cursor.y);
            modelMatrix *= transform2D::Translate(-turretInfoVector[i].position.x, -turretInfoVector[i].position.y);
            RenderMesh2D(meshes[turretInfoVector[i].meshID], shaders["VertexColor"], modelMatrix);
        }
    }


}

void Tema1::PlaceTurret(float deltaTimeSeconds) {
    
    modelMatrix = glm::mat3(1);
    for (const auto& meshPair : meshesDynamic) {
        RenderMesh2D(meshPair.second, shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = glm::mat3(1);
    for (auto it = squareInfoVector.begin(); it != squareInfoVector.end(); ++it) {
        if (it->makeDeleteAnimation == true) {
		    
            cout << "make delete\n";
            cout << "final scale: " << final_scale << endl;
            final_scale -= 5 * deltaTimeSeconds;
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(it->position.x - 20, it->position.y);
			modelMatrix *= transform2D::Scale(final_scale, final_scale);

			modelMatrix *= transform2D::Translate(-it->position.x + 20, -it->position.y);
			RenderMesh2D(it->mesh, shaders["VertexColor"], modelMatrix);
			
			if (final_scale <= 0) {
                cout << "here\n";
                it->makeDeleteAnimation = false;
                final_scale = 1;
            }
        }
    }
    
}

void Tema1::EnemyAnimation(float deltaTimeSeconds) {
    
    
    if (generationTime >= increase_difficulty) {
		int randomLine = RandomNumber(1, 3);
        int randomColor = RandomNumber(0, 3);
        cout << "random line : " << randomLine << endl;
        cout << "random color : " << randomColor << endl;

        // make enemy animation

        int Y = 0;


        switch (randomLine) {
            case 1: {
                Y = squareInfoVector[0].position.y;
            }
                break;
            case 2: {
                Y = squareInfoVector[3].position.y;
            }
                break;

            case 3: {
                Y = squareInfoVector[6].position.y;
            }
                  break;
            default:
                cout << "ERROR at random\n";
                break;
        }

        glm::vec3 position = glm::vec3(1280 + 100, Y, 0); // 100 = enemy size
        infoEnemy enemy(position, 3, 0, enemyID, 0, randomColor, randomLine, false, false, 1, false, false);
        enemyInfoVector.push_back(enemy);

        Mesh* hexagone = object2D::CreateHexagone("hexagone" + std::to_string(enemyID), enemy.position, 100, colors[randomColor], true);
        AddMeshToListEnemy(hexagone);

        // add color to line
        line.colorHere[randomLine][randomColor]++;

        enemyID++;
		generationTime = 0;
        

        // increase difficulty per enemy
        if (increase_difficulty >= 4.5f)
            increase_difficulty -= 0.5f;
        // increase speed per enemy
        if (speed_difficulty <= 130.0f)
            speed_difficulty += 10.0f;

        cout << "finish" << endl;

        for (int i = 1; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                cout << line.colorHere[i][j] << " ";
            cout << endl;
        }
	}


    // for every enemy
    for (auto enemy = enemyInfoVector.begin(); enemy != enemyInfoVector.end(); ++enemy) {
        for (auto pro = projectileInfoVector.begin(); pro != projectileInfoVector.end();) {
            if (enemy->line == pro->line && enemy->color == pro->color && enemy->position.x - pro->position.x <= (50 + 30)) {
               
                enemy->health--;

                // delete projectile
                meshesProjectile.erase("star" + std::to_string(pro->projectileID));
                pro = projectileInfoVector.erase(pro);

                // delete enemy (first scale, after delete)
                if (enemy->health == 0) {
					enemy->scaleAnimation = true;
				}

            } else
                ++pro;

        }
    }
    
    // render enemy
    for (auto it = enemyInfoVector.begin(); it != enemyInfoVector.end(); ++it) {
        if (it->scaleAnimation == true) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(-it->moveTime, 0);
            modelMatrix *= transform2D::Translate(1380, it->position.y);
            modelMatrix *= transform2D::Scale(it->scaleTime, it->scaleTime);
            modelMatrix *= transform2D::Translate(-1380, -it->position.y);
            RenderMesh2D(meshesEnemy["hexagone" + std::to_string(it->enemyID)], shaders["VertexColor"], modelMatrix);
            
            it->scaleTime -= 5 * deltaTimeSeconds;
            if(it->scaleTime <= 0)
				it->deleteEnemy = true;
        }
        else {
            modelMatrix = glm::mat3(1);


            // speed of enemy
            it->moveTime += speed_difficulty * deltaTimeSeconds;
            modelMatrix *= transform2D::Translate(-it->moveTime, 0);

            // UPDATE ENEMY POSITION
            it->position.x -= speed_difficulty * deltaTimeSeconds;
            // RENDER ENEMY

            // DELETE HIM !! WITHOUT SCALE !!
            if (it->position.x <= 100 && it->deleteHealth == false) {
                healthCount--;
                it->deleteHealth = true;
            }

            RenderMesh2D(meshesEnemy["hexagone" + std::to_string(it->enemyID)], shaders["VertexColor"], modelMatrix);
        }
    }

    // delete enemy
    for (auto it = enemyInfoVector.begin(); it != enemyInfoVector.end();) {


        if ((it->moveTime >= 1200 + 100 || it->deleteEnemy == true) && it->scaleAnimation == true) {
            // Remove the color from line
            line.colorHere[it->line][it->color]--;

            // Remove the corresponding mesh
            meshesEnemy.erase("hexagone" + std::to_string(it->enemyID));
            // Erase the element using the iterator
            it = enemyInfoVector.erase(it);
        }
        else {
            // Move to the next element

            ++it;
        }
    }



}

void Tema1::CheckShootAnimation() {
	
    // pentru fiecare patrat
    for (int i = 0; i < 9; i++) {
        // daca avem o tureta
        if (squareInfoVector[i].place == true) {
            int linie = i / 3 + 1;
            // daca avem linia cu inamici
            if (line.colorHere[linie][squareInfoVector[i].color] > 0) {
                squareInfoVector[i].shoot = true;
            }
            else {
				squareInfoVector[i].shoot = false;
			}
            
	    }
    }

}

void Tema1::ShootAnimation(float deltaTimeSeconds) {

    //if (delayTime >= 0.2) {
		CheckShootAnimation();
    //}

    if (delayTime >= 1.2f) {

        for (int i = 0; i < 9; i++) {
            if (squareInfoVector[i].shoot == true) {


                int linie = i / 3 + 1;

                // create a projectile
                glm::vec3 projectilePos = glm::vec3(squareInfoVector[i].position.x, squareInfoVector[i].position.y, 2);

                infoProjectile projectile(projectilePos, 60, squareInfoVector[i].color, 0, projectileID, linie);
                // add to infoProjectile vector
                projectileInfoVector.push_back(projectile);

                // create a mesh
                Mesh* pro = object2D::CreateStar("star" + std::to_string(projectileID), projectile.position, projectile.dimension, colors[squareInfoVector[i].color], true);
                projectileID++;
                AddMeshToListProjectile(pro);
             
            }
        }

        delayTime = 0;
    }
}

void Tema1::RenderProjectile(float deltaTimeSeconds) {

    for (auto it = projectileInfoVector.begin(); it != projectileInfoVector.end();) {
		
        modelMatrix = glm::mat3(1);

        modelMatrix *= transform2D::Translate(it->position.x, it->position.y);
        modelMatrix *= transform2D::Rotate(-0.01 * it->moveTime);
        modelMatrix *= transform2D::Translate(-it->position.x, -it->position.y);
        
        // projectile move speed
		it->moveTime += 200 * deltaTimeSeconds;


        modelMatrix *= transform2D::Translate(it->moveTime, 0);

        // UPDATE PROJECTILE POSITION
        it->position.x += 200 * deltaTimeSeconds;

		RenderMesh2D(meshesProjectile["star" + std::to_string(it->projectileID)], shaders["VertexColor"], modelMatrix);
        
        if (it->moveTime >= 1200) {
			// Remove the corresponding mesh
			meshesProjectile.erase("star" + std::to_string(it->projectileID));
			// Erase the element using the iterator
			it = projectileInfoVector.erase(it);
		}
        else {
			// Move to the next element
			++it;
		}
	}

}

void Tema1::ColisionEnemyProjectile() {

    // store current position of enemy
    // store current position of projectile

}

void Tema1::GenerateStars(float deltaTimeSeconds) {


    // generation time of 2.5 units and number of stars < 8
    if (generationStarsTime >= 2.5f && meshesStars.size() < 8.0f) {

        float dimension = 80;
        // safe margins
        int randomX = RandomNumber(0 + dimension, 1280 - dimension);
        int randomY = RandomNumber(0 + dimension, 720 - dimension);
		
        // Z >>
        infoStar star(glm::vec3(randomX, randomY, 10), dimension, 0, starsID, false);
        starsInfoVector.push_back(star);
        Mesh *starMesh = object2D::CreateStar("click_star" + std::to_string(starsID), star.position, star.dimension, glm::vec3(1, 1, 0), true);
        AddMeshToListStars(starMesh);
        starsID++;
		
        generationStarsTime = 0;
    }
}

void Tema1::RenderStars() {
    
    modelMatrix = glm::mat3(1);
    // render stars
    for (const auto& meshPair : meshesStars) {
        RenderMesh2D(meshPair.second, shaders["VertexColor"], modelMatrix);
    }

    // delete stars
    for (auto it = starsInfoVector.begin(); it != starsInfoVector.end(); ) {
        if (it->deleteStar == true) {
			meshesStars.erase("click_star" + std::to_string(it->starID));
			it = starsInfoVector.erase(it);
		}
        else {
			++it;
		}
	}
    
    
}

void Tema1::RenderStarsBar() {

    // cout << starCount;

    modelMatrix = glm::mat3(1);
    for(int i = 0 ; i < starCount && i < 12; i++)
		RenderMesh2D(meshesBarStars["star_bar" + std::to_string(i + 1)], shaders["VertexColor"], modelMatrix);

}

void Tema1::RenderHealthBar() {

    for (int i = 0; i < healthCount; i++) {
        RenderMesh2D(meshesBarHealth["heart" + std::to_string(i + 1)], shaders["VertexColor"], modelMatrix);
    }

}

void Tema1::Update(float deltaTimeSeconds)
{
    time += 1 * deltaTimeSeconds;
    generationTime += 1 * deltaTimeSeconds;
    delayTime += 1 * deltaTimeSeconds;
    generationStarsTime += 1 * deltaTimeSeconds;
    debugTime += 1 * deltaTimeSeconds;

    RenderScene();
    DragAndDrop();
    PlaceTurret(deltaTimeSeconds);
    // CheckTurretTime();
    EnemyAnimation(deltaTimeSeconds);
    ShootAnimation(deltaTimeSeconds);
    RenderProjectile(deltaTimeSeconds);
    ColisionEnemyProjectile();
    ColisionEnemyTurret();

    GenerateStars(deltaTimeSeconds);
    RenderStars();
    RenderStarsBar();

 
    RenderHealthBar();

    if (healthCount == 0)
        window->Close();

 //   if (debugTime >= 5) {
 //       // for (int i = 0; i < 9; i++) {
 //          // cout << "Square " << i + 1 << " color: " << squareInfoVector[i].color << "place: " << squareInfoVector[i].place << endl;
 //          // cout << "Square " << i + 1 << " line: " << squareInfoVector[i].line << endl;
 //          // cout << "Square " << i + 1 << " col: " << squareInfoVector[i].col << endl;
 //       // }

 //       cout << "spawn_rate : " << increase_difficulty << " & ";
 //       cout << "speed_difficulty " << speed_difficulty << endl;


 //       debugTime = 0;
	//}

}


void Tema1::FrameEnd()
{

}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{   

    // ON CLICK NORMAL

    glm::vec4 marginAreaTurret[4];

    for (int i = 0; i < 4; i++) {
        float marginX1 = turretInfoVector[i].margin1.x;
        float marginX2 = turretInfoVector[i].margin2.x;
        float marginY1 = turretInfoVector[i].margin1.y;
        float marginY2 = turretInfoVector[i].margin2.y;
        marginAreaTurret[i] = glm::vec4(marginX1, marginX2, marginY1, marginY2);
    }



    for (int i = 0; i < 4; i++) {
        if (button == GLFW_MOUSE_BUTTON_2) {
            // cout << "turretA info " << turretA.margin2.x << " " << turretA.margin2.y << endl;
            // cout << marginAreaTurret[0].x << " " << marginAreaTurret[0].y << " " << marginAreaTurret[0].z << " " << marginAreaTurret[0].t << endl;
            if (mouseX >= marginAreaTurret[i].x && mouseX <= marginAreaTurret[i].y &&
                720 - mouseY >= marginAreaTurret[i].z && 720 - mouseY <= marginAreaTurret[i].w) {
                turretInfoVector[i].click = true;
                cout << "TURRET HERE\n";
            }
        }
    }
    
    // ON CLICK DELETE
    if (button == GLFW_MOUSE_BUTTON_3) {
        cout << "Square : " << DeleteSquareTurret() << endl;
    }

    if (button == GLFW_MOUSE_BUTTON_2) {
        for (auto it = starsInfoVector.begin(); it != starsInfoVector.end(); ++it) {
            // check condition delete
            if (it->checkCircle(mouseX, 720 - mouseY)) {
				//cout << "star here\n";
                
                if(starCount < 12)
                    starCount++;
                
                it->deleteStar = true;
                
                // for deleting just ONE STAR
                break;
			}
	
        }
            
	}

}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{   
    


    // Add mouse button release event
    for(int i = 0 ; i < 4 ; i++)
        if (button == GLFW_MOUSE_BUTTON_2) {

            if(turretInfoVector[i].click)
                cout << "Square : " << AddSquareTurret(turretInfoVector[i]) << endl;

            turretInfoVector[i].click = false;
        }

    
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
