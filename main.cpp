#include "raylib.h"
#include "gra.hpp"
#include "skladnik.hpp"
#include "pizza.hpp"
#include "punkty.hpp"
#include "klient.hpp"
#include "muzyka.hpp" 
#include "zamowienia.hpp"

enum Ekran { MENU, GRA, PRZYGOTOWYWANIE_PIZZY, PIEC_ZBLIŻENIE, WYJSCIE, INSTRUKCJA, PROFIL,KONIEC_GRY};

int main() {
    const int szerokoscOkna = 800, wysokoscOkna = 600;
    InitWindow(szerokoscOkna, wysokoscOkna, "BIT OF PIZZA");
    SetTargetFPS(60);

    Texture2D tloMenu = LoadTexture("obrazki/menu.png");
    Texture2D tloGry = LoadTexture("obrazki/tloGry.png");
    Texture2D pizzaMan = LoadTexture("obrazki/pizzaman.png");
    Texture2D tloPrzygotowania = LoadTexture("obrazki/blat.png");
    Texture2D pizzaObrazek = LoadTexture("obrazki/pizza.png");
    Texture2D sosObrazek = LoadTexture("obrazki/sos.png");
    Texture2D serObrazek = LoadTexture("obrazki/ser.png");
    Texture2D pieczarkiObrazek = LoadTexture("obrazki/pieczarki.png");
    Texture2D cebulaObrazek = LoadTexture("obrazki/cebula.png");
    Texture2D peperoniObrazek = LoadTexture("obrazki/peperoni.png");
    Texture2D piecZblizenie = LoadTexture("obrazki/piec.png");
    Texture2D pizzaSurowa = LoadTexture("obrazki/pizzaSurowa.png");
    Texture2D pizzaUpieczona = LoadTexture("obrazki/pizzaUpieczona.png");
    Texture2D pizzaPrzypalona = LoadTexture("obrazki/pizzaSpalona.png");
    Texture2D tloProfil = LoadTexture("obrazki/profil.png");
    Texture2D instrukcja = LoadTexture("obrazki/instrukcja.png");
    Texture2D koniec = LoadTexture("obrazki/koniecgry.png");

    bool pizzaWPiecu = false;
    float czasWPiecu = 0.0;
    int stanPieczenia = 0;
    bool pizzaPoprawniePrzypieczona = true;
    int aktualnePunkty = 0;
    int zadowoleniKlienci = 0;
    int zrobionePizze = 0;

    Muzyka muzyka("muzyka/muzyka.ogg"); 
    
    Ekran aktualnyEkran = MENU;
    int PizzaManX = 100, PizzaManY = 100; 

    Klienci klient;

    Rectangle walek = { 411, 50, 239, 81 };

    bool pizzaDodana = false;
    int pizzaX = 0;
    int pizzaY = 0;

    Rectangle blatGorny = { 76, 215, 239, 98 }; 
    Rectangle blatDolny = { 26, 414, 315, 102 }; 

    Rectangle sos = { 198, 26, 133, 100 }; 
    bool sosDodany = false;
    int sosX = 0; 
    int sosY = 0;

    Rectangle ser = { 49, 31, 133, 105 }; 
    bool serDodany = false;
    int serX = 0; 
    int serY = 0;

    Rectangle pieczarki = { 47, 169, 143, 107 }; 
    bool pieczarkiDodane = false;
    int pieczarkiX = 0; 
    int pieczarkiY = 0;

    
    Rectangle cebula = { 51, 296, 142, 108 }; 
    bool cebulaDodana = false;
    int cebulaX = 0; 
    int cebulaY = 0;

    Rectangle peperoni = { 49, 446, 153, 113 }; 
    bool peperoniDodane = false;
    int peperoniX = 0; 
    int peperoniY = 0;

    Rectangle piec = { 320, 97, 183, 150 }; 

    Rectangle piecPizza = { 215, 154, 392, 325 }; 
    bool piecPizzaDodane = false;
    int piecPizzaX = 0; 
    int piecPizzaY = 0;

    bool czyPizzaPrzygotowana = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        muzyka.Aktualizuj(); 

        if (aktualnyEkran == MENU) {
            DrawTexture(tloMenu, 0, 0, WHITE);

            int tekstX = szerokoscOkna / 2 - MeasureText("BIT OF PIZZA", 40) / 2;
            int tekstY = 100;
            DrawText("BIT OF PIZZA", tekstX - 2, tekstY, 40, BLACK);
            DrawText("BIT OF PIZZA", tekstX + 2, tekstY, 40, BLACK);
            DrawText("BIT OF PIZZA", tekstX, tekstY - 2, 40, BLACK);
            DrawText("BIT OF PIZZA", tekstX, tekstY + 2, 40, BLACK);
            DrawText("BIT OF PIZZA", tekstX - 1, tekstY - 1, 40, BLACK);
            DrawText("BIT OF PIZZA", tekstX + 1, tekstY - 1, 40, BLACK);
            DrawText("BIT OF PIZZA", tekstX - 1, tekstY + 1, 40, BLACK);
            DrawText("BIT OF PIZZA", tekstX + 1, tekstY + 1, 40, BLACK);
            DrawText("BIT OF PIZZA", tekstX, tekstY, 40, WHITE);

        Rectangle przyciskStart = { szerokoscOkna / 2 - 100, 150, 200, 50 };
        DrawRectangleRec(przyciskStart, ORANGE);
        DrawText("Start", przyciskStart.x + 60, przyciskStart.y + 10, 30, WHITE);

        Rectangle przyciskProfil = { szerokoscOkna / 2 - 100, 220, 200, 50 };
        DrawRectangleRec(przyciskProfil, ORANGE);
        DrawText("Profil", przyciskProfil.x + 60, przyciskProfil.y + 10, 30, WHITE);

        Rectangle przyciskInstrukcja = { szerokoscOkna / 2 - 100, 290, 200, 50 };
        DrawRectangleRec(przyciskInstrukcja, ORANGE);
        DrawText("Instrukcja", przyciskInstrukcja.x + 23, przyciskInstrukcja.y + 10, 30, WHITE);

        Rectangle przyciskWyjscie = { szerokoscOkna / 2 - 100, 360, 200, 50 };
        DrawRectangleRec(przyciskWyjscie, ORANGE);
        DrawText("Wyjscie", przyciskWyjscie.x + 50, przyciskWyjscie.y + 10, 30, WHITE);


            if (CheckCollisionPointRec(GetMousePosition(), przyciskStart) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                aktualnyEkran = GRA;
            if (CheckCollisionPointRec(GetMousePosition(), przyciskProfil) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                aktualnyEkran = PROFIL;
            if (CheckCollisionPointRec(GetMousePosition(), przyciskInstrukcja) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                aktualnyEkran = INSTRUKCJA;
            if (CheckCollisionPointRec(GetMousePosition(), przyciskWyjscie) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                aktualnyEkran = WYJSCIE;
        }

        // GRA
        else if (aktualnyEkran == GRA) {
            UruchomGre(tloGry); 
             
            klient.rysuj();
            klient.aktualizuj();
            klient.sprawdzInterakcje(PizzaManX,PizzaManY, pizzaDodana,  sosDodany,  serDodany, peperoniDodane,  pieczarkiDodane, cebulaDodana,pizzaPoprawniePrzypieczona);
            aktualnePunkty = klient.getPunkty();
            zrobionePizze = klient.getZrobionePizze();
            zadowoleniKlienci = klient.getZadowoleniKlienci();

            if (klient.czyGraSkonczona()) {
                aktualnyEkran = KONIEC_GRY;
                aktualnePunkty = 0;
        }

            
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec((Vector2){(float)mouseX, (float)mouseY}, blatGorny) ||
                    CheckCollisionPointRec((Vector2){(float)mouseX, (float)mouseY}, blatDolny)) {
                    aktualnyEkran = PRZYGOTOWYWANIE_PIZZY;
                }
                if (CheckCollisionPointRec((Vector2){(float)mouseX, (float)mouseY}, piec)) {
                    aktualnyEkran = PIEC_ZBLIŻENIE;
                }
                
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                aktualnyEkran = MENU;
            }

        }
        // PRZYGOTOWANIE
        else if (aktualnyEkran == PRZYGOTOWYWANIE_PIZZY) {
            DrawTexture(tloPrzygotowania, 0, 0, WHITE);
            DrawText(TextFormat("Pozostaly czas: %i s", klient.pozostalyCzas()), 10, 10, 20, WHITE);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, walek)) {
                    pizzaDodana = true;
                    czyPizzaPrzygotowana = true;
                    pizzaX = 0; 
                    pizzaY = 0;
                }
                if (pizzaDodana){
                    if (CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, sos)) {
                        sosDodany = true;
                        sosX = 0;
                        sosY = 0;
                    }
                    if (CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, ser)) {
                        serDodany = true;
                        serX = 0;
                        serY = 0;
                    }
                    if (CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, pieczarki)) {
                        pieczarkiDodane = true;
                        pieczarkiX = 0;
                        pieczarkiY = 0;
                    }
                    if (CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, cebula)) {
                        cebulaDodana = true;
                        cebulaX = 0;
                        cebulaY = 0;
                    }
                    if (CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, peperoni)) {
                        peperoniDodane = true;
                        peperoniX = 0;
                        peperoniY = 0;
                    }
                }
            }
            if (pizzaDodana) {
                DrawTexture(pizzaObrazek, pizzaX, pizzaY, WHITE);
            }
            if (sosDodany) {
                DrawTexture(sosObrazek, sosX, sosY, WHITE);
            }            
            if (serDodany) {
                DrawTexture(serObrazek, sosX, sosY, WHITE);
            }    
            if (pieczarkiDodane) {
                DrawTexture(pieczarkiObrazek, sosX, sosY, WHITE);
            }    
            if (cebulaDodana) {
                DrawTexture(cebulaObrazek, sosX, sosY, WHITE);
            }    
            if (peperoniDodane) {
                DrawTexture(peperoniObrazek, sosX, sosY, WHITE);
            }
            
            if (!pizzaDodana) {
                DrawText("Kliknij walek, aby rozpoczac!", 300, 550, 30, WHITE);
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                aktualnyEkran = GRA;
                // pizzaDodana = false;
                // sosDodany = false;
                // serDodany = false;
                // pieczarkiDodane = false;
                // cebulaDodana = false;
                // peperoniDodane = false;
                // bez sensu tak robic bo nigdy sie nie bedzie to prawdziwe 
            }

            if (IsKeyPressed(KEY_SPACE)) {
                pizzaDodana = false;
                sosDodany = false;
                serDodany = false;
                pieczarkiDodane = false;
                cebulaDodana = false;
                peperoniDodane = false;
        }

        // PIEC
        }else if (aktualnyEkran == PIEC_ZBLIŻENIE) {
            DrawTexture(piecZblizenie, 0, 0, WHITE);
            DrawText(TextFormat("Pozostaly czas: %i s", klient.pozostalyCzas()), 10, 10, 20, WHITE);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec((Vector2){(float)GetMouseX(), (float)GetMouseY()}, piecPizza)) {
                    if (czyPizzaPrzygotowana) {
                        piecPizzaDodane = true;
                        pizzaWPiecu = true;
                        czasWPiecu = 0.0;
                        stanPieczenia = 0;
                    }                    
            }
        }
            if (pizzaWPiecu) {
                czasWPiecu += GetFrameTime();
        
                if (czasWPiecu >= 10.0) {
                    stanPieczenia = 2; 
                } else if (czasWPiecu >= 5.0) {
                    stanPieczenia = 1; 
                }
        
                if (stanPieczenia == 0){
                    DrawTexture(pizzaSurowa, piecPizzaX, piecPizzaY, WHITE);
                    pizzaPoprawniePrzypieczona = false; 
                }
                else if (stanPieczenia == 1){
                    DrawTexture(pizzaUpieczona, piecPizzaX, piecPizzaY, WHITE);
                    pizzaPoprawniePrzypieczona = true; 
                }
                else if (stanPieczenia == 2){
                    DrawTexture(pizzaPrzypalona, piecPizzaX, piecPizzaY, WHITE);
                    pizzaPoprawniePrzypieczona = false; 
                }
            }
            if (!czyPizzaPrzygotowana) {
                DrawText("Najpierw przygotuj pizze!", 220, 30, 30, WHITE);
           }
           if (IsKeyPressed(KEY_SPACE)) {
            pizzaWPiecu = false;
            piecPizzaDodane = false; 
            pizzaDodana = false;
            czyPizzaPrzygotowana = false;
        }
        
            if (IsKeyPressed(KEY_BACKSPACE)) {
                aktualnyEkran = GRA;
                // pizzaWPiecu = false;
                // piecPizzaDodane = false;
                // czyPizzaPrzygotowana = false;
            }
        }
    
        else if(aktualnyEkran == INSTRUKCJA){
            DrawTexture(instrukcja, 0, 0, WHITE);
        
            if (IsKeyPressed(KEY_BACKSPACE)) {
                aktualnyEkran = MENU;
            }
        }
        else if(aktualnyEkran == PROFIL){
            DrawTexture(tloProfil, 0, 0, WHITE);
            DrawText(TextFormat("%i", aktualnePunkty), 460, 175, 20, BLACK);
            DrawText(TextFormat("%i", zrobionePizze), 460, 265, 20, BLACK); 
            DrawText(TextFormat("%i", zadowoleniKlienci), 460, 385, 20, BLACK);               
            if (IsKeyPressed(KEY_BACKSPACE)) {
                aktualnyEkran = MENU;
            }
        }   
        
        else if(aktualnyEkran == KONIEC_GRY){
            DrawTexture(koniec,0,0,WHITE);
        }
        else if (aktualnyEkran == WYJSCIE) {
            break;
        }
        

        EndDrawing();
    }
    
    UnloadTexture(tloMenu);
    UnloadTexture(tloGry);
    CloseWindow();
    UnloadTexture(pizzaObrazek);
    UnloadTexture(sosObrazek);
    UnloadTexture(serObrazek);
    UnloadTexture(pieczarkiObrazek);
    UnloadTexture(cebulaObrazek);
    UnloadTexture(peperoniObrazek);
    UnloadTexture(pizzaSurowa);
    UnloadTexture(pizzaUpieczona);
    UnloadTexture(pizzaPrzypalona);
    UnloadTexture(tloProfil);
    muzyka.Zakonczenie(); 
    
    return 0;
}
