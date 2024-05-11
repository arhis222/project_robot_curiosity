#include "observateur.h"
Etat initial(){
    return Init;
}

Etat transition(Etat e,Alphabet c){
    //if(e!=Err){
    switch(e){
        case Init:
            switch(c){
                case M:
                    return Mes;
                case A:
                    return Err;
                case D:
                case G:
                    return Init;
            }
        case Err:
            return Err;
        case Mes:
            switch(c){
                case M:
                    return Mes;
                case A:
                case D:
                case G:
                    return Init;
            }
    default:
        return e;
    }
}

Etat transition_2(Etat e,Alphabet c){
    //if(e!=Err){
    switch(e){
        case Init:
            switch(c){
                case A:
                    return Init;
                case D:
                    return Une_d;
                case G:
                    return Une_g;
                default:
                    return e;
            }
        
        case Une_d:
            switch(c){
                case A:
                case G:
                    return Init;
                case D:
                    return Deux_d;
                default:
                    return e;
            }
        case Une_g:
            switch(c){
                case A:
                case D:
                    return Init;
                case G:
                    return Deux_g;
                default:
                    return e;
            }
        case Deux_d:
            switch(c){
                case A:
                    return Init;
                case D:
                    return Trois_d;
                case G:
                    return Une_d;
                default:
                    return e;
            }
        case Deux_g:
            switch(c){
                case A:
                    return Init;
                case D:
                    return Une_g;
                case G:
                    return Trois_g;
                default:
                    return e;
            }
        case Trois_d:
            switch(c){
                case A:
                    return Init;
                case D:
                    return Err;
                case G:
                    return Deux_d;
                default:
                    return e;
            }
        case Trois_g:
            switch(c){
                case A:
                    return Init;
                case D:
                    return Deux_g;
                case G:
                    return Err;
                default:
                    return e;
            }
        case Err:
            return Err;
        
    default:
        return e;
    }
}

int est_final(Etat e){
    if(e==Init || e==Mes){
        return 1;
    }
    return 0;
}

int est_final_2(Etat e){
    if(e==Init || e==Une_d || e==Une_g || e==Deux_d || e==Deux_g || e==Trois_d || e==Trois_g){
        return 1;
    }
    return 0;
}
    



