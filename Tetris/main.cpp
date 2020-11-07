#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int M = 20; // semble �tre les lignes
const int N = 10; // semble �tre les colonnes


// je dirais qu'il s'agit d'un tableau bidimensionnel d'entier initialis� � zero.
int field[M][N] = { 0 };

// pas encore clair � quoi ca correspond
struct Point
{
	int x, y;
} a[4], b[4];

// tableau bidimensionnel 7*4: pas clair pourquoi ca correspond � tel ou tel forme.
int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};


int main()
{

	srand(time(0));
	RenderWindow window(VideoMode(320, 480), "The Game!");
	Texture t1;
	t1.loadFromFile("images/tiles.png");
	Sprite s(t1);

	int dx = 0; bool rotate = 0; int colorNum = 1;
	float timer = 0, delay = 0.3;

	Clock clock;

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e))
		{


			if (e.type == Event::Closed)
				window.close();
			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Up) rotate = true; // fleche du haut pour declencher la rotation.
				else if (e.key.code == Keyboard::Left) dx = -1; // va � gauche
				else if (e.key.code == Keyboard::Right) dx = 1; // va � droite
		}



		

		//if (timer > delay)
		//{

			for (int i = 0; i < 1; i++) { b[i] = a[i]; a[i].x += dx; }
			window.clear(Color::White);


			for (int i = 0; i < 1; i++)
			{
				s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
				s.setPosition(a[i].x * 18, a[i].y * 18);
				//       s.move(28,31); //offset
				window.draw(s);
			}

			//   window.draw(s);
			window.display();
			timer = 0; dx = 0;
		//}
	}
	return 0;
}

///////Tick//////

// si on depasse le 0.3 seconde
//if (timer>delay)
//  {

//    // on descend d'une ligne (le + car par du zero en haut � gauche?)
//    for (int i=0;i<4;i++) { b[i]=a[i]; a[i].y+=1; }


//  }


/////////draw//////////



// parcourt tout les cases de la grille pour remplir avec les bons objets.
//    for (int i=0;i<M;i++)
//     for (int j=0;j<N;j++)
//       {
//
//         // s est le sprite pour Square j'imagine.
//         if (field[i][j]==0) continue;
//         s.setTextureRect(IntRect(field[i][j]*18,0,18,18));// r�cup�re un seul carr� de l'image? 
//         s.setPosition(j*18,i*18);
////         s.move(28,31); //offset
//         window.draw(s);
//       }
//
//
//    // pas encore clair
//    for (int i=0;i<4;i++)
//      {
//        s.setTextureRect(IntRect(colorNum*18,0,18,18));
//        s.setPosition(a[i].x*18,a[i].y*18);
//        s.move(28,31); //offset
//        window.draw(s);
//      }

//    window.draw(frame); // pas clair



// la fin bug, il n'arrive pas � nous dire qu'on a perdu.
// chaque figure n'a qu'une seul couleur
// en appuyant sur la fleche du haut seulement (et plusieurs fois) on gen�re la rotation.


//
//#include <SFML/Graphics.hpp>
//#include <time.h>
//using namespace sf;
//
//const int M = 20; // semble �tre les lignes
//const int N = 10; // semble �tre les colonnes
//
//
//// je dirais qu'il s'agit d'un tableau bidimensionnel d'entier initialis� � zero.
//int field[M][N] = { 0 };
//
//// pas encore clair � quoi ca correspond
//struct Point
//{
//    int x, y;
//} a[4], b[4];
//
//// tableau bidimensionnel 7*4: pas clair pourquoi ca correspond � tel ou tel forme.
//int figures[7][4] =
//{
//    1,3,5,7, // I
//    2,4,5,7, // Z
//    3,5,4,6, // S
//    3,5,4,7, // T
//    2,3,5,7, // L
//    3,5,7,6, // J
//    2,3,4,5, // O
//};
//
//
//// pas encore claire
//bool check()
//{
//
//    // regarde si on depasse � gauche ou droite et renvoie zero (empeche l'action)
//    // deuxi�me ligne avec field : je pige pas encore.
//    // sinon renvoi A (autorise le mouvement).
//    for (int i = 0; i < 4; i++)
//        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
//        else if (field[a[i].y][a[i].x]) return 0;
//
//    return 1;
//};


//int main()
//{
//
//    // initilisation des nombres al�atoire en C++
//    srand(time(0));
//
//
//    // cr�ation de la f�n�tre principale SFML avec un titre et 320 pixel de large et 480 de haut.
//
//    RenderWindow window(VideoMode(320, 480), "The Game!");
//
//
//    // trois textures charg�es.
//    Texture t1, t2, t3;
//    t1.loadFromFile("images/tiles.png");
//    //t2.loadFromFile("images/background.png");
//    //t3.loadFromFile("images/frame.png");
//
//
//    // transformation en sprite (pas exactement clair mais colle avec tutorial)
//    Sprite s(t1); //, background(t2), frame(t3);
//
//
//    // initialisation de quelques variables.
//    int dx = 0; bool rotate = 0; int colorNum = 1;
//    float timer = 0, delay = 0.3;
//
//
//    // initilialisation de l'objet clock
//    Clock clock;
//
//
//    // demarrage de la boucle principale
//    while (window.isOpen())
//    {
//
//        // a chaque iteration, r�cup�re le temps pass� en seconde et incremente le timer?
//        float time = clock.getElapsedTime().asSeconds();
//        clock.restart();
//        timer += time;
//
//        // ne pas appeler l'objet event car nom reserv� en c++
//        Event e;
//        while (window.pollEvent(e))
//        {
//
//            // Event:: Closer ou Event::KeyPressed correspondent � des enums trouvables dans la doc je crois.
//            if (e.type == Event::Closed)
//                window.close();
//
//
//
//            if (e.type == Event::KeyPressed)
//                if (e.key.code == Keyboard::Up) rotate = true; // fleche du haut pour declencher la rotation.
//                else if (e.key.code == Keyboard::Left) dx = -1; // va � gauche
//                else if (e.key.code == Keyboard::Right) dx = 1; // va � droite
//        }
//
//
//        // augmente la vitesse de descente de l'objet j'imagine.
//        if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;
//
//        //// <- Move -> ///
//
//        // deplacer � gauche ou droite l'objet suivant que on appuie sur fleche left ou right
//
//        // garde a en m�moire dans b si par hasard le mouvement n'est pas autoris�
//        for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }
//
//        // execute la fonction check, regarder si elle vaut 0 ou 1: signifie que le deplacement est interdit ou doit
//        // s'arr�ter( quand check est �gale � zero, le mouvement s'arr�te ou n'est pas autoris�??)
//
//
//        // si check renvoie zero, on refuse le mouvement et r�initiliase � l'ancienne position a, c'est � dire b.
//        if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
//
//        //////Rotate//////
//        if (rotate)
//        {
//
//            // ce centre de rotation fait qu'au pire, une case peut se retrouver plus haut de 1 or on voit que l'on demarre une case en dessous de la grille
//            // pour g�rer ce cas de figure.
//            Point p = a[1]; //center of rotation
//            for (int i = 0; i < 4; i++)
//            {
//                int x = a[i].y - p.y;
//                int y = a[i].x - p.x;
//                a[i].x = p.x - x;
//                a[i].y = p.y + y;
//            }
//            if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
//        }
//
//        ///////Tick//////
//
//        // si on depasse le 0.3 seconde
//        if (timer > delay)
//        {
//
//            // on descend d'une ligne (le + car par du zero en haut � gauche?)
//            for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }
//
//            // si est arriv� en bas, check est sans doute �gal � zero.
//            if (!check())
//            {
//                for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;
//
//                colorNum = 1 + rand() % 7;
//
//                // choisis al�atoirement la nouvelle figure.
//                int n = rand() % 7;
//                for (int i = 0; i < 4; i++)
//
//                    // pas clair
//                {
//                    a[i].x = figures[n][i] % 2;
//                    a[i].y = figures[n][i] / 2;
//                }
//            }
//
//
//            // on reinitialise le timer � zero.
//            timer = 0;
//        }
//
//        ///////check lines//////////
//
//        // pas encore clair.
//        int k = M - 1;
//        for (int i = M - 1; i > 0; i--)
//        {
//            int count = 0;
//            for (int j = 0; j < N; j++)
//            {
//                if (field[i][j]) count++;
//                field[k][j] = field[i][j];
//            }
//            if (count < N) k--;
//        }
//
//        dx = 0; rotate = 0; delay = 0.3;
//
//        /////////draw//////////
//        window.clear(Color::White);
//        window.draw(background);
//
//
//        // parcourt tout les cases de la grille pour remplir avec les bons objets.
//        for (int i = 0; i < M; i++)
//            for (int j = 0; j < N; j++)
//            {
//
//                // s est le sprite pour Square j'imagine.
//                if (field[i][j] == 0) continue;
//                s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));// r�cup�re un seul carr� de l'image? 
//                s.setPosition(j * 18, i * 18);
//                s.move(28, 31); //offset
//                window.draw(s);
//            }
//
//
//        // pas encore clair
//        for (int i = 0; i < 4; i++)
//        {
//            s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
//            s.setPosition(a[i].x * 18, a[i].y * 18);
//            s.move(28, 31); //offset
//            window.draw(s);
//        }
//
//        window.draw(frame); // pas clair
//        window.display();
//    }
//
//    return 0;
//}
