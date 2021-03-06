/*
 * Copyright (C) 2015-2020 Alibaba Group Holding Limited
 */

#ifndef __AIRCRAFTBATTLE_H__
#define __AIRCRAFTBATTLE_H__

#include "../menu.h"

extern MENU_TYP aircraftBattle;

int aircraftBattle_init(void);
int aircraftBattle_uninit(void);
void aircraftBattle_task(void);
void aircraftBattle_key_handel(key_code_t key_code);

/*
    -> x
    ____________________
    |         |    icon|
 |  |       of_y       |
 \/ |         |        |
  y |--of_x--x*        |
    |__________________|
*/
typedef struct
{
    icon_t *icon;
    int offset_x;
    int offset_y;
} map_t; // 贴图

typedef struct
{
    map_t **maplist;      // 贴图指针数组
    uint8_t const_length; // 用于数组
    uint8_t const_delay;  // 延迟几个周期换
    uint8_t isDestory;
    void (*reset_func)(void *);
    uint8_t act_index; // 用于遍历
    uint8_t timer;     // 计数用的
} act_seq_t;           // 动作序列 每个对象可以有多个

typedef enum
{
    UP,
    LEFT,
    RIGHT,
    DOWN
} my_craft_dir_e_t;

typedef struct
{
    int pos_x;
    int pos_y;
    act_seq_t **act_seq_list;
    uint8_t act_list_len; // 用于改变飞机状态的
    uint8_t act_type;     // 用于改变飞机状态的
    uint8_t speed;
    uint8_t harm;
    uint8_t full_life;
    uint8_t cur_life;
    // 只保留运行时需要的成员

} plane_t; // base obj 每种机型单独一个结构体吧 没法继承 会更麻烦

typedef struct
{
    int start_x;
    int start_y;
    act_seq_t **act_seq_list;
    uint8_t act_list_len;
    uint8_t act_type; // 用于改变飞机状态的
    uint8_t speed;
    uint8_t harm;
    uint8_t full_life;
    uint8_t cur_life;
    unsigned int range;
    int pos_x;
    int pos_y;
    int active;
    // 只保留运行时需要的成员
} bullet_t;

//
void move_MyCraft(plane_t *my_craft, my_craft_dir_e_t dir);
void shut_MyCraft(plane_t *my_craft);
void reset_MyCraft(plane_t *craft);

//
void move_Scraft(plane_t *s_craft);

//
void move_Mcraft(plane_t *m_craft);

//
void move_Lcraft(plane_t *l_craft);
void reset_Lcraft(plane_t *craft);
void shut_layzer_Lcraft(plane_t *l_craft); // ready + shut index++ 激光是跟着机身的 所以作为一体

//
void move_bullet(bullet_t *bullet);

void aircraftBattle_cover_draw(int *draw_index);

// Lcraft
//      nomal
static uint8_t icon_data_Lcraft_32_32[] = {0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0xB8, 0xB8, 0xBC, 0xBC, 0xBE, 0xFF, 0xFF, 0xFF, 0xFF, 0xBE, 0xB6, 0xB6, 0x34, 0x74, 0x70, 0x70, 0xD0, 0x90, 0xB0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x1C, 0x16, 0x12, 0x5B, 0x5F, 0xCF, 0xCF, 0xC7, 0xC7, 0xE7, 0x77, 0x3F, 0xBF, 0xFF, 0xFF, 0xEF, 0x6F, 0x2F, 0x2F, 0x6F, 0x6F, 0x5F, 0xDF, 0xDF, 0xDE, 0xDE, 0x9A, 0xB2, 0x36, 0x1C, 0x18, 0x10, 0x38, 0x68, 0x48, 0xDA, 0xFA, 0xF3, 0xF3, 0xE3, 0xE3, 0xE7, 0xEE, 0xFC, 0xFD, 0xFF, 0xFF, 0xF7, 0xF6, 0xF4, 0xF4, 0xF6, 0xF6, 0xFA, 0xFB, 0xFB, 0x7B, 0x7B, 0x59, 0x4D, 0x6C, 0x38, 0x18, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x0C, 0x1D, 0x1D, 0x3D, 0x3D, 0x7D, 0xFF, 0xFF, 0xFF, 0xFF, 0x7D, 0x6D, 0x6D, 0x2C, 0x2E, 0x0E, 0x0E, 0x0B, 0x09, 0x0D, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00};
static uint8_t icon_mask_Lcraft_32_32[] = {0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0xB8, 0xB8, 0xBC, 0xBC, 0xBE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF6, 0xF6, 0xF4, 0xF4, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x1C, 0x1E, 0x1E, 0x5F, 0x5F, 0xCF, 0xCF, 0xC7, 0xC7, 0xE7, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xDF, 0xDF, 0xDE, 0xDE, 0x9E, 0xBE, 0x3E, 0x1C, 0x18, 0x10, 0x38, 0x78, 0x78, 0xFA, 0xFA, 0xF3, 0xF3, 0xE3, 0xE3, 0xE7, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xFB, 0xFB, 0x7B, 0x7B, 0x79, 0x7D, 0x7C, 0x38, 0x18, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x0C, 0x1D, 0x1D, 0x3D, 0x3D, 0x7D, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x6F, 0x6F, 0x2F, 0x2F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00};
static icon_t icon_Lcraft_32_32 = {icon_data_Lcraft_32_32, 32, 32, icon_mask_Lcraft_32_32};

//      destory
static uint8_t icon_data_Lcraft_destory2_32_32[] = {0x00, 0x30, 0x46, 0xB8, 0x70, 0x10, 0x20, 0x8D, 0xAC, 0x98, 0x3C, 0x1B, 0x53, 0x16, 0x04, 0x0E, 0x22, 0x02, 0x54, 0x64, 0x40, 0x40, 0xC0, 0xA6, 0xA0, 0xE3, 0xC0, 0xF8, 0x14, 0xCE, 0x15, 0x18, 0x00, 0x00, 0x16, 0x81, 0x0A, 0x49, 0x0D, 0x4B, 0x43, 0xC1, 0xE4, 0x10, 0x29, 0x0C, 0x09, 0x5A, 0x07, 0x62, 0x82, 0x0C, 0x27, 0x08, 0x09, 0xCB, 0x3F, 0xC0, 0x85, 0x0A, 0xA0, 0x31, 0x10, 0x00, 0x00, 0x14, 0x07, 0x40, 0x03, 0xC8, 0x72, 0xE0, 0x41, 0x61, 0x02, 0x8A, 0x40, 0x00, 0x7C, 0x2B, 0x26, 0x0C, 0xB0, 0x1B, 0x62, 0x49, 0x1A, 0x51, 0x03, 0x0B, 0x19, 0x01, 0x81, 0x0C, 0x00, 0x18, 0x40, 0x50, 0x38, 0x00, 0x0C, 0x68, 0x18, 0x01, 0x18, 0x14, 0x68, 0x06, 0x0A, 0x54, 0x0A, 0x50, 0x4D, 0x01, 0x28, 0x20, 0xDC, 0x08, 0x33, 0x49, 0x40, 0x87, 0x04, 0x09, 0x01, 0x04, 0x08, 0x08};
static icon_t icon_Lcraft_destory2_32_32 = {icon_data_Lcraft_destory2_32_32, 32, 32, NULL};

static uint8_t icon_data_Lcraft_destory1_32_32[] = {0x20, 0x27, 0x24, 0xE6, 0x7C, 0x58, 0x00, 0xC0, 0xE0, 0xE9, 0xC1, 0xE3, 0x26, 0x0E, 0x54, 0xD4, 0x58, 0xB0, 0x10, 0x5C, 0xF0, 0xC4, 0xF4, 0xE8, 0x88, 0x14, 0xFA, 0xFA, 0xC8, 0x84, 0x04, 0x80, 0x78, 0xF4, 0x44, 0xA3, 0x5D, 0x6E, 0x78, 0x39, 0x1F, 0x5F, 0xEB, 0x60, 0xC8, 0x40, 0xCC, 0xC7, 0x67, 0xC7, 0x9C, 0x88, 0xF0, 0x7C, 0xF1, 0x57, 0x63, 0x31, 0x7F, 0x7F, 0x8F, 0xED, 0xFC, 0x78, 0x10, 0x91, 0x4C, 0x58, 0xBF, 0x19, 0x40, 0xC3, 0x16, 0xBF, 0xDF, 0xCE, 0x6A, 0x17, 0xD9, 0xA8, 0xCC, 0xBA, 0xB6, 0xC0, 0xFB, 0x39, 0x9F, 0xD3, 0xC4, 0x7C, 0x89, 0xEE, 0x02, 0x8D, 0x83, 0x00, 0x02, 0x11, 0x18, 0x18, 0xC8, 0x27, 0x23, 0x3B, 0x10, 0x39, 0x0B, 0x87, 0xAE, 0x21, 0x07, 0x1F, 0x16, 0x02, 0x33, 0xFB, 0x89, 0x27, 0x39, 0x35, 0x2F, 0xEE, 0x4B, 0xD8, 0xA8, 0x70, 0x22, 0x42};
static icon_t icon_Lcraft_destory1_32_32 = {icon_data_Lcraft_destory1_32_32, 32, 32, NULL};

static uint8_t icon_data_Lcraft_destory0_32_32[] = {0x00, 0x00, 0x06, 0x38, 0x70, 0x30, 0x38, 0xBD, 0xFC, 0xB8, 0x3E, 0x3F, 0x73, 0xF7, 0xB7, 0x0E, 0x26, 0x12, 0x14, 0x74, 0x70, 0x70, 0xD0, 0xF6, 0xA0, 0xE3, 0xC0, 0x98, 0x04, 0x06, 0x41, 0x40, 0x08, 0x1C, 0x16, 0x10, 0x5A, 0x5F, 0xCF, 0xCD, 0xC3, 0xC1, 0xE5, 0x34, 0x2F, 0x9E, 0xFF, 0xFA, 0x8F, 0x2B, 0x23, 0xCB, 0x67, 0x6C, 0x59, 0xDF, 0x5F, 0xFE, 0xDE, 0x9A, 0xB2, 0x37, 0x1C, 0x18, 0x10, 0x38, 0x68, 0x48, 0x92, 0xFA, 0xF3, 0xF0, 0xE3, 0xE1, 0xE3, 0xEA, 0xC0, 0x38, 0x7F, 0x2B, 0x67, 0x7E, 0xF4, 0xE4, 0xE0, 0xC0, 0x2A, 0x33, 0xFB, 0x7B, 0x7B, 0x59, 0x4D, 0x6C, 0x38, 0x18, 0x40, 0x50, 0x78, 0x0C, 0x0C, 0x08, 0x1D, 0x11, 0x39, 0x3C, 0x7C, 0xDF, 0xDB, 0xDF, 0xEE, 0x5C, 0x4D, 0x0D, 0x2C, 0x3E, 0xDE, 0x0F, 0x3B, 0x49, 0x4F, 0x8F, 0x00, 0x31, 0x60, 0x00, 0x00, 0x00};
static icon_t icon_Lcraft_destory0_32_32 = {icon_data_Lcraft_destory0_32_32, 32, 32, NULL};

//      Layer Ready
static uint8_t icon_data_Lcraft_LayerReady0_3_3[] = {0x02, 0x05, 0x02};
static icon_t icon_Lcraft_LayerReady0_3_3 = {icon_data_Lcraft_LayerReady0_3_3, 3, 3, NULL};

static uint8_t icon_data_Lcraft_LayerReady1_3_3[] = {0x05, 0x02, 0x05};
static icon_t icon_Lcraft_LayerReady1_3_3 = {icon_data_Lcraft_LayerReady1_3_3, 3, 3, NULL};

// Mcraft
//      nomal
static uint8_t icon_data_Mcraft_12_12[] = {0x01, 0x03, 0x6F, 0xFE, 0x9C, 0xFC, 0xF8, 0x98, 0x98, 0x98, 0x90, 0x90, 0x08, 0x0C, 0x0F, 0x07, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00};
static uint8_t icon_mask_Mcraft_12_12[] = {0x01, 0x03, 0x6F, 0xFE, 0xFC, 0xFC, 0xF8, 0x98, 0x98, 0x98, 0x90, 0x90, 0x08, 0x0C, 0x0F, 0x07, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00};
static icon_t icon_Mcraft_12_12 = {icon_data_Mcraft_12_12, 12, 12, icon_mask_Mcraft_12_12};
//      destory

// Mycraft
//      nomal
static uint8_t icon_mask_Mycraft_19_19[] = {0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC8, 0xE8, 0xF8, 0xFE, 0xFF, 0xFF, 0x3E, 0x0C, 0x0C, 0x0C, 0x0C, 0x07, 0x07, 0x0F, 0x0F, 0x0F, 0x0F, 0x1F, 0x1F, 0x9F, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE2, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x07, 0x03, 0x01, 0x01, 0x01, 0x01};
static uint8_t icon_data_Mycraft0_19_19[] = {0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC8, 0x68, 0xB8, 0x4E, 0x13, 0xFF, 0x3E, 0x0C, 0x0C, 0x00, 0x00, 0x07, 0x05, 0x0D, 0x0A, 0x08, 0x0F, 0x1A, 0x1A, 0x9A, 0xB2, 0xE8, 0x97, 0x42, 0xFF, 0xE2, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00};
static icon_t icon_Mycraft0_19_19 = {icon_data_Mycraft0_19_19, 19, 19, icon_mask_Mycraft_19_19};

static uint8_t icon_data_Mycraft1_19_19[] = {0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC8, 0x68, 0xB8, 0x4E, 0x13, 0xFF, 0x3E, 0x0C, 0x00, 0x0C, 0x00, 0x07, 0x05, 0x0D, 0x0A, 0x08, 0x0F, 0x1A, 0x1A, 0x9A, 0xB2, 0xE8, 0x97, 0x42, 0xFF, 0xE2, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x07, 0x03, 0x01, 0x00, 0x01, 0x00};
static icon_t icon_Mycraft1_19_19 = {icon_data_Mycraft1_19_19, 19, 19, icon_mask_Mycraft_19_19};

static uint8_t icon_data_Mycraft2_19_19[] = {0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC8, 0x68, 0xB8, 0x4E, 0x13, 0xFF, 0x3E, 0x0C, 0x00, 0x00, 0x0C, 0x07, 0x05, 0x0D, 0x0A, 0x08, 0x0F, 0x1A, 0x1A, 0x9A, 0xB2, 0xE8, 0x97, 0x42, 0xFF, 0xE2, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x07, 0x03, 0x01, 0x00, 0x00, 0x01};
static icon_t icon_Mycraft2_19_19 = {icon_data_Mycraft2_19_19, 19, 19, icon_mask_Mycraft_19_19};

//      destory
static uint8_t icon_data_Mycraft_destory0_19_19[] = {0x00, 0x14, 0xC2, 0x90, 0xC9, 0x80, 0xD8, 0x85, 0xC8, 0x78, 0xB9, 0x4E, 0x13, 0xCF, 0x3E, 0x4C, 0x80, 0x08, 0x00, 0x09, 0xC0, 0x0D, 0x0A, 0x28, 0x4F, 0x5A, 0x22, 0x8A, 0xB2, 0xC9, 0x97, 0x42, 0xF8, 0xE2, 0x80, 0x12, 0x04, 0x60, 0x00, 0x00, 0x00, 0x01, 0x01, 0x04, 0x02, 0x01, 0x00, 0x01, 0x00, 0x03, 0x02, 0x07, 0x03, 0x01, 0x02, 0x00, 0x00};
static icon_t icon_Mycraft_destory0_19_19 = {icon_data_Mycraft_destory0_19_19, 19, 19, NULL};

static uint8_t icon_data_Mycraft_destory1_19_19[] = {0x00, 0x14, 0xF2, 0xD2, 0xC9, 0x8A, 0xD8, 0x85, 0x08, 0x38, 0x99, 0x46, 0x13, 0xC7, 0x36, 0xDC, 0x80, 0x8C, 0x00, 0x09, 0xC0, 0x0D, 0x02, 0x28, 0xDF, 0x5A, 0x22, 0x8B, 0xB2, 0xC9, 0x97, 0xC2, 0x38, 0x72, 0x90, 0x52, 0x2C, 0x60, 0x00, 0x00, 0x00, 0x01, 0x01, 0x04, 0x02, 0x03, 0x02, 0x03, 0x00, 0x03, 0x02, 0x05, 0x03, 0x01, 0x02, 0x00, 0x00};
static icon_t icon_Mycraft_destory1_19_19 = {icon_data_Mycraft_destory1_19_19, 19, 19, NULL};

static uint8_t icon_data_Mycraft_destory2_16_16[] = {0x68, 0x80, 0x22, 0x20, 0x94, 0x21, 0x00, 0x88, 0x26, 0x01, 0x04, 0x30, 0x8C, 0x30, 0xA0, 0x00, 0x02, 0x40, 0x4A, 0x36, 0x14, 0x08, 0xA0, 0x00, 0x10, 0x04, 0x10, 0x0C, 0x10, 0x00, 0x00, 0x04};
static icon_t icon_Mycraft_destory2_16_16 = {icon_data_Mycraft_destory2_16_16, 16, 16, NULL};

// Scraft
static uint8_t icon_data_Scraft_7_8[] = {0x24, 0x18, 0x3C, 0xC3, 0x66, 0x3C, 0x18};
static uint8_t icon_mask_Scraft_7_8[] = {0x3C, 0x18, 0x3C, 0xFF, 0x7E, 0x3C, 0x18};
static icon_t icon_Scraft_7_8 = {icon_data_Scraft_7_8, 7, 8, icon_data_Scraft_7_8};

// bullet
static uint8_t icon_data_bullet_2_1[] = {0x01, 0x01};
static icon_t icon_bullet_2_1 = {icon_data_bullet_2_1, 2, 1, NULL};

// Game UI
static uint8_t icon_data_craft_life_5_5[] = {0x0C, 0x1E, 0x0F, 0x1E, 0x0C};
static icon_t icon_craft_life_5_5 = {icon_data_craft_life_5_5, 5, 5, NULL};

static uint8_t icon_data_mini_start_3_3[] = {0x02, 0x05, 0x02};
static icon_t icon_mini_start_3_3 = {icon_data_mini_start_3_3, 3, 3, NULL};

static uint8_t img_data_craft_bg_132_64[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0xF8, 0x08, 0x00, 0xF8, 0x20, 0x20, 0xF8, 0x00, 0xF8, 0xA8, 0xA8, 0x88, 0x00, 0x00, 0x00, 0xB8, 0xA8, 0xA8, 0xE8, 0x00, 0xF8, 0x28, 0x28, 0x38, 0x00, 0xF0, 0x28, 0x28, 0xF0, 0x00, 0xF8, 0x88, 0x88, 0xD8, 0x00, 0xF8, 0xA8, 0xA8, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0xA0,
    0xB0, 0x4C, 0xB0, 0xA0, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xA0, 0x40, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x40, 0x40, 0xC0, 0xA0, 0x20, 0x22, 0x20, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x14, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x60, 0x10, 0x60, 0x1E, 0x00, 0x7C, 0x0A, 0x0A, 0x7C, 0x00, 0x7E, 0x12, 0x12, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x6C, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x01, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x50, 0x78, 0x28, 0xFC, 0xF6, 0xD3, 0x93, 0x09, 0x09, 0x0B, 0x0E, 0x08, 0x05, 0x05, 0x05, 0x04, 0x03, 0x03, 0x02, 0x02, 0x02, 0x03, 0x07, 0x07, 0x8F, 0xBF, 0x7F, 0xF3, 0xF3, 0xFB, 0xFB, 0xFB, 0x79, 0x7D, 0x3E, 0x1E, 0x0E, 0x0E, 0x06, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x60, 0xA0, 0x90, 0x50, 0x20, 0xA0, 0xA0, 0x40, 0x40, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x14, 0x08, 0x00, 0x00, 0x00, 0x80,
    0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x40, 0xC0, 0xA0, 0x60, 0x50, 0xB0, 0xA8, 0x58, 0x54, 0x2C, 0x2C, 0x18, 0x10, 0x08, 0x08, 0x04, 0x02, 0x02, 0x01, 0x89, 0x04, 0x44, 0xA2, 0x41, 0xB3, 0x9F, 0x7F, 0xFF, 0xFF, 0x7E, 0x3C, 0x10, 0x80, 0x40, 0x40, 0xA0, 0xA0, 0x50, 0xD0, 0xA8, 0x98, 0xDC, 0x4A, 0x2A, 0x15, 0x1D, 0x0A, 0x0A, 0x05, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x04, 0x1E, 0xE1, 0x01, 0x00, 0x00, 0x03, 0x04, 0x18, 0x20, 0xC0, 0x01, 0x01, 0x02, 0x02, 0x02, 0x04, 0x04, 0x04, 0x08, 0x08, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0xA0, 0xAF, 0x74, 0x46, 0x26, 0x13, 0x11, 0x09, 0x09, 0x05, 0x06, 0x02, 0x02, 0x01, 0x00, 0x80, 0x80, 0xC0, 0xA0, 0x60, 0x30, 0x28, 0x18, 0x0C, 0x0C, 0xC6, 0xB5, 0x9B, 0x4E, 0x4B, 0xA6, 0xA5, 0x53, 0x32, 0xA9, 0x55, 0x54, 0x2A, 0x2A, 0x15, 0x15, 0x0A, 0x0D, 0x05, 0x02, 0x02, 0x01, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x1C, 0x36, 0x1C, 0x08, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x03, 0x1C, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x86, 0x88, 0x70, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10, 0x08, 0x08,
    0x04, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x80, 0x80, 0xC0, 0x60, 0x60, 0x30, 0x30, 0x18, 0x0C, 0x0C, 0x06, 0x05, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0xC0, 0x60, 0x58, 0x2C, 0x27, 0x15, 0x1A, 0x0A, 0x05, 0x05, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x0C, 0x17, 0x14, 0x12, 0x0A, 0x09, 0x05, 0xC4, 0xC6, 0xD8, 0xE0, 0x10, 0x10, 0x08, 0x08, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x80, 0x00, 0xE0, 0x18, 0x0C, 0x0C, 0x06, 0x06, 0x03, 0xE1, 0x1D, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x18, 0x04, 0x03, 0x00, 0x00, 0x00, 0xF0, 0x50, 0x50, 0x20, 0x00, 0xF0, 0x50, 0xD0, 0x20, 0x00, 0xF0, 0x50, 0x50, 0x10, 0x00, 0x70, 0x50, 0x50, 0xD0, 0x00, 0x70, 0x50, 0x50, 0xD0, 0x02, 0x00, 0x00, 0x00, 0xF0, 0xC0, 0x30, 0x00,
    0x70, 0x40, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0xF2, 0x10, 0x00, 0xF4, 0x10, 0x10, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x90, 0x80, 0xC0, 0x80, 0xE0, 0xA0, 0xD0, 0x10, 0x40, 0x84, 0xEA, 0x84, 0x00, 0x00, 0x7E, 0xF7, 0x8F, 0xF7, 0xFB, 0x9F, 0xDF, 0xBF, 0xFE, 0xF0, 0xF0, 0xE8, 0xD0, 0xE8, 0x50, 0x68, 0x34, 0x28, 0xF4,
    0x3A, 0xAC, 0xAA, 0x55, 0x56, 0xAB, 0xFA, 0x0F, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x78, 0x47, 0x40, 0xA0, 0xA0, 0xA0, 0x90, 0x90, 0x50, 0x50, 0xF0, 0x60, 0x10, 0x0C, 0x03, 0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10, 0x09, 0x08, 0x38, 0x78, 0xF8, 0xF9, 0x78, 0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0xF1, 0x91, 0x91, 0x91, 0x90, 0x01, 0x01, 0x11, 0x11, 0xF0, 0x10, 0x10, 0x00,
    0x01, 0xC0, 0xA1, 0x90, 0xA0, 0xC0, 0x01, 0x00, 0xF0, 0x90, 0x90, 0x90, 0x60, 0x01, 0x00, 0x10, 0x11, 0xF1, 0x11, 0x11, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x54, 0xAA, 0x5E, 0xAB, 0x55, 0xAA, 0x5D, 0xAA, 0x71, 0xAA, 0x1D, 0xAA, 0x5E, 0xCB, 0x49, 0x23, 0xEE, 0x13, 0x31, 0xB9, 0x40, 0x39, 0x0B, 0x07, 0x07, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xC0, 0x38, 0x04, 0x03, 0x01, 0x00, 0x00, 0xC0, 0x3C, 0x07, 0x04, 0x04, 0x04, 0x84, 0x74, 0x0E, 0x01, 0x01, 0x01, 0x01, 0x00, 0x80, 0xC0, 0x60, 0x10, 0x0C, 0x02, 0x01, 0x82, 0x82, 0x41, 0x41, 0x20, 0x30, 0x90, 0x88, 0x48, 0x48, 0x24, 0x24, 0x92, 0x52, 0x51, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x07, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x00, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static icon_t img_craft_bg_132_64 = {img_data_craft_bg_132_64, 132, 64, NULL};

#endif