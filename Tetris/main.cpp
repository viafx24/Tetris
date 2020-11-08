// la fin bug, il n'arrive pas � nous dire qu'on a perdu.
// chaque figure n'a qu'une seul couleur
// en appuyant sur la fleche du haut seulement (et plusieurs fois) on gen�re la rotation.



#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int M = 20; // semble �tre les lignes
const int N = 10; // semble �tre les colonnes


// je dirais qu'il s'agit d'un tableau bidimensionnel d'entier initialis� � zero.
int field[M][N] = {0};

// Le programme fonctionne avec deux structures contenant 4 carr�s (avec une forme diff�rente).
// on se sert r�guli�rement de b pour stocker a avant modif de a. chaque carr� contient bien s�r 
// une coordonn� X et Y
struct Point
{int x,y;} a[4], b[4];

// tableau bidimensionnel 7*4: avec une gestion fine du modulo et de la division, on r�cr�e les 
// coordonn�es correspondant � la bonne forme.

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


// Fonction de v�rification de que l'on ne depasse � droite ou gauche 
// et surtout quand on atteint le bas qui correpond soit � M=20
// soit � l'empilement des cases qui empechent d'aller plus bas.

bool check()
{
   for (int i=0;i<4;i++)

// gauche, droite ou tout en bas: empeche de depasser.
      if (a[i].x<0 || a[i].x>=N || a[i].y>=M) return 0;

// ligne fine qui signifie si atteint l'empilement, empeche de continuer.
// la subtilit� r�side dans le fait que le if fonctionne si diff�rent de zero et non pas �gal � 1; 
// autrement dit, la condition est vrai et renvoie zero si l'int�rieur du if est �gal  � 2,3  etc...
      else if (field[a[i].y][a[i].x]) return 0;

   return 1;
};

// boucle principale
int main()
{

    // initilisation des nombres al�atoire en C++
    srand(time(0));     


    // cr�ation de la f�n�tre principale SFML avec un titre et 320 pixel de large et 480 de haut.

    RenderWindow window(VideoMode(320, 480), "The Game!");


    // trois textures charg�es.
    Texture t1,t2,t3;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/background.png");
    t3.loadFromFile("images/frame.png"); // celle je ne pige pas encore son int�r�t.


    // transformation en sprite (pas exactement clair mais colle avec tutorial)
    Sprite s(t1), background(t2), frame(t3);


    // initialisation de quelques variables.
    int dx=0; bool rotate=0; int colorNum=1;
    float timer=0,delay=0.3; 


    // initilialisation de l'objet clock
    Clock clock;


    // demarrage de la boucle principale
    while (window.isOpen())
    {

        // a chaque iteration, r�cup�re le temps pass� en seconde et incremente le timer.
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();// on remet � zero le compteur. la ligne du dessus pourra�t �tre inutile car 
        //clock.restart renvoie le temp ecoul�.

        // on incr�mente pour d�tecter quand on d�passe 0.3 seconde.
        timer+=time;

        // ne pas appeler l'objet event car nom reserv� en c++
        Event e;
        while (window.pollEvent(e))
        {

            // Event:: Closer ou Event::KeyPressed correspondent � des enums trouvables dans la doc je crois.
            if (e.type == Event::Closed)
                window.close();


           
            if (e.type == Event::KeyPressed)
              if (e.key.code==Keyboard::Up) rotate=true; // fleche du haut pour declencher la rotation.
              else if (e.key.code==Keyboard::Left) dx=-1; // va � gauche
              else if (e.key.code==Keyboard::Right) dx=1; // va � droite
        }


     // augmente la vitesse de descente de l'objet j'imagine.
    // pas clair pourquoi on ne le met pas dans les events.
    // a noter que cela n'est valable que tant que le doigt reste appuyer sur la touche.

    if (Keyboard::isKeyPressed(Keyboard::Down)) delay=0.05;

    //// <- Move -> ///

    // deplacer � gauche ou droite l'objet suivant que on appuie sur fleche left ou right

    // garde a en m�moire dans b si par hasard le mouvement n'est pas autoris�
    for (int i=0;i<4;i++)  { b[i]=a[i]; a[i].x+=dx; }

    // execute la fonction check, regarder si elle vaut 0 ou 1: signifie que le deplacement est interdit ou doit
    // s'arr�ter( quand check est �gale � zero, le mouvement s'arr�te ou n'est pas autoris�??)

    // si check renvoie zero, on refuse le mouvement et r�initiliase � l'ancienne position a, c'est � dire b.
    if (!check()) for (int i=0;i<4;i++) a[i]=b[i];

    //////Rotate//////
    // je n'ai pas regard� en d�tail comment est pens� la rotation, je suis s�r que les equations sont correctes.
    // toujours l'appel � la fonction check si on d�passe.

    if (rotate)
      {
        Point p = a[1]; //center of rotation
        for (int i=0;i<4;i++)
          {
            int x = a[i].y-p.y;
            int y = a[i].x-p.x;
            a[i].x = p.x - x;
            a[i].y = p.y + y;
           }
           if (!check()) for (int i=0;i<4;i++) a[i]=b[i];
      }

    ///////Tick//////

    // si on depasse le 0.3 seconde
    if (timer>delay)
      {

        // on descend d'une ligne (le + car par du zero en haut � gauche?)
        for (int i=0;i<4;i++) { b[i]=a[i]; a[i].y+=1; }

        // si on atteint le haut de l'empilement. C'est une subtilit� car 
        // les autres cas possibles de check ont d�ja �t� trait�s. il ne reste donc 
        // que le cas de l'arriv� sur l'empilement.

        // si on arrive sur l'empilement on va �crire dans le tableau bidimensionnel
        // la couleur de la case pour la garder en m�moire et pouvoir recre�er le tableau. 
        if (!check())
        {
         for (int i=0;i<4;i++) field[b[i].y][b[i].x]=colorNum;

         // on choisit une nouvelle couleur aleatoire pour la nouvelle forme comprise entre 1 et 7 
         // le zero est reserv� pour les cases vides.

         colorNum=1+rand()%7;

         // choisis al�atoirement la nouvelle figure.
         int n=rand()%7; // entre 0 et 7
         for (int i=0;i<4;i++)

             // subilit� du code avec le modulo et la division pour g�n�rer la bonne forme.
           {
            a[i].x = figures[n][i] % 2;
            a[i].y = figures[n][i] / 2;
           }
        }

        // comme on a atteint le sommet de l'empilement et g�n�r� une nouvellrme forme,
        // on reinitialise le timer � zero.
         timer=0;
      }

    ///////check lines//////////

// un code subtile qui detecte quand une ligne est compl�te.
// dans ce cas, count==N et k qui correspond � la ligne du dessus
// n'est pas decrement�. Il en result un changement sequentiel de
// tout les lignes les unes apr�s les autres (avec disparition de la premi�re)
// la deuxi�me ligne prenant la valeur de la ligne en dessous et ainsi de suite.


    int k=M-1;
    for (int i=M-1;i>0;i--) // on part du bas!! c'est le point contre-intuitif
    {
        int count=0;
        for (int j=0;j<N;j++)
        {
            if (field[i][j]) count++; // si if n'est pas �gal � zero!!
            field[k][j]=field[i][j]; 
        }
        if (count<N) k--;
    }

    dx=0; rotate=0; delay=0.3;

    /////////draw//////////
    window.clear(Color::White);    
    window.draw(background);
     

// parcourt tout les cases de la grille pour remplir les empilements devenus statiques.
    for (int i=0;i<M;i++)
     for (int j=0;j<N;j++)
       {

         // s est le sprite pour Square j'imagine.
         if (field[i][j]==0) continue; // si zero ne fait rien et passe � l'iteration suivante
         // field[i][j] contient le numero de la couleur (de 1 � 7) ce qui permet �galement 
         // d'aller chercher le bon x dans le sprite contenant tout les carr�s sur une ligne.

         s.setTextureRect(IntRect(field[i][j]*18,0,18,18));// charge la bonne texture (le carr� de bonne couleur)
         s.setPosition(j*18,i*18); // les carr�s faisant 18 pixels de large, ce sera toujous un multiple de 18
         s.move(28,31); //offset probablement li� au background qui mange de l'espace � gauche (pour prendre en compte le cadre dor�)
         window.draw(s);
       }

// pour afficher la forme en cour de descente
    for (int i=0;i<4;i++)
      {
        s.setTextureRect(IntRect(colorNum*18,0,18,18));
        s.setPosition(a[i].x*18,a[i].y*18);
        s.move(28,31); //offset
        window.draw(s);
      }

    // il restait un dernier myst�re � elucider : pourquoi la premi�re forme ne contient qu'un carr�.
    // la r�ponse: elle est initialis� � A (0,0) pour les 4 cases mais dans la boucle, un 1 appara�t pour les 
    // quatres m�mes cases car le y est initialis� � chaque descente, d'o� le 0,1 puis 0,2 pui 0,3
    // ce qui correspond bien � un carr� seul qui descend.


    window.draw(frame); // les carr�s en bas ne sont pas parfaitement allign� avec la frame
    // on redescine la frame apr�s les carr�s pour que ce soit un peu plus esthetique.
    window.display();
    }

    return 0;
}
