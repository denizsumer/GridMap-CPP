/*
* Generated by SGWrapperGen - DO NOT EDIT!
*
* SwinGame wrapper for C - Characters
*
* Wrapping sgCharacters.pas
*/

#include "SGSDK.h"
#include "Characters.h"

#include "Types.h"

direction_angles character_angle_at(character c, int32_t index)
{
    return sg_Characters_CharacterAngleAt(c, index);
}

int32_t character_angle_max_at(character c, int32_t index)
{
    return sg_Characters_CharacterAngleMaxAt(c, index);
}

int32_t character_angle_min_at(character c, int32_t index)
{
    return sg_Characters_CharacterAngleMinAt(c, index);
}

int32_t character_angles_length(character c)
{
    return sg_Characters_CharacterAnglesLength(c);
}

void character_character_name(character c, char *result)
{
    sg_Characters_CharacterCharacterName(c, result);
}

int32_t character_current_direction(character c)
{
    return sg_Characters_CharacterCurrentDirection(c);
}

int32_t character_current_state(character c)
{
    return sg_Characters_CharacterCurrentState(c);
}

int32_t character_direction_count(character c)
{
    return sg_Characters_CharacterDirectionCount(c);
}

void character_directions(character c, string_array result, int32_t result_len)
{
    sg_Characters_CharacterDirections(c, result, result_len);
}

void character_filename(character c, char *result)
{
    sg_Characters_CharacterFilename(c, result);
}

void character_name(character c, char *result)
{
    sg_Characters_CharacterName(c, result);
}

character character_named(const char *name)
{
    return sg_Characters_CharacterNamed(name);
}

void character_set_current_direction(character c, int32_t direction)
{
    sg_Characters_CharacterSetCurrentDirection(c, direction);
}

void character_set_current_state(character c, int32_t state)
{
    sg_Characters_CharacterSetCurrentState(c, state);
}

void character_set_name(character c, const char *name)
{
    sg_Characters_CharacterSetName(c, name);
}

void character_set_type(character c, const char *name)
{
    sg_Characters_CharacterSetType(c, name);
}

void character_set_value(character c, int32_t idx, float val)
{
    sg_Characters_CharacterSetValue(c, idx, val);
}

#ifdef __cplusplus

void character_set_value(character c, const char *name, float val)
{
    sg_Characters_CharacterSetValueByName(c, name, val);
}

#endif

void character_set_value_by_name(character c, const char *name, float val)
{
    sg_Characters_CharacterSetValueByName(c, name, val);
}

bool character_shown_layers_at(character c, int32_t index)
{
    return sg_Characters_CharacterShownLayersAt(c, index) != 0;
}

sprite character_sprite(character c)
{
    return sg_Characters_CharacterSprite(c);
}

int32_t character_state_count(character c)
{
    return sg_Characters_CharacterStateCount(c);
}

void character_states(character c, string_array result, int32_t result_len)
{
    sg_Characters_CharacterStates(c, result, result_len);
}

void character_type(character c, char *result)
{
    sg_Characters_CharacterType(c, result);
}

float character_value_at(character c, int32_t index)
{
    return sg_Characters_CharacterValueAt(c, index);
}

int32_t character_value_count(character c)
{
    return sg_Characters_CharacterValueCount(c);
}

void character_value_names(character c, string_array result, int32_t result_len)
{
    sg_Characters_CharacterValueNames(c, result, result_len);
}

void draw_character(character c)
{
    sg_Characters_DrawCharacter(c);
}

void draw_character_sprite(character c)
{
    sg_Characters_DrawCharacterSprite(c);
}

void draw_character_with_stationary(character c, int32_t stationaryState, int32_t state)
{
    sg_Characters_DrawCharacterWithStationary(c, stationaryState, state);
}

#ifdef __cplusplus

void free_character(character &c)
{
    sg_Characters_FreeCharacter(&c);
}

#endif

void free_character(character *c)
{
    sg_Characters_FreeCharacter(c);
}

bool has_character(const char *name)
{
    return sg_Characters_HasCharacter(name) != 0;
}

character load_character(const char *filename)
{
    return sg_Characters_LoadCharacter(filename);
}

character load_character_named(const char *name, const char *filename)
{
    return sg_Characters_LoadCharacterNamed(name, filename);
}

void release_all_characters()
{
    sg_Characters_ReleaseAllCharacters();
}

void release_character(const char *name)
{
    sg_Characters_ReleaseCharacter(name);
}

void set_active_layer(character c)
{
    sg_Characters_SetActiveLayer(c);
}

void toggle_layer_visibility(character c, int32_t index)
{
    sg_Characters_ToggleLayerVisibility(c, index);
}

bool update_direction_animation(character c)
{
    return sg_Characters_UpdateDirectionAnimation(c) != 0;
}

bool update_direction_animation_with_stationary(character c, int32_t state, int32_t newState)
{
    return sg_Characters_UpdateDirectionAnimationWithStationary(c, state, newState) != 0;
}

