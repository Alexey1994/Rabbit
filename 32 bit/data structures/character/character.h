#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED


typedef char Character;


function Boolean is_number     (Character character);
function Boolean is_hex_number (Character character);
function Boolean is_letter     (Character character);
function Boolean is_space      (Character character);


#include "character.c"

#endif // CHARACTER_H_INCLUDED
