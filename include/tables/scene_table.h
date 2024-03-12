/**
 * Scene Table
 *
 * DEFINE_SCENE should be used for all scenes (with or without a title card, see argument 2)
 *    - Argument 1: Name of the scene segment in spec
 *    - Argument 2: Name of the title card segment in spec, or `none` for no title card
 *    - Argument 3: Enum value for this scene
 *    - Argument 4: Scene draw config index
 *    - Argument 5: ? (Unknown)
 *    - Argument 6: ? (Unknown)
 */
/* 0x00 */ DEFINE_SCENE(ydan_scene, g_pn_06, SCENE_DEKU_TREE, SDC_DEKU_TREE, 1, 2)
/* 0x01 */ DEFINE_SCENE(ddan_scene, g_pn_08, SCENE_DODONGOS_CAVERN, SDC_DODONGOS_CAVERN, 1, 3)
/* 0x02 */ DEFINE_SCENE(bdan_scene, g_pn_07, SCENE_JABU_JABU, SDC_JABU_JABU, 1, 4)
/* 0x03 */ DEFINE_SCENE(Bmori1_scene, g_pn_01, SCENE_FOREST_TEMPLE, SDC_FOREST_TEMPLE, 2, 5)
/* 0x04 */ DEFINE_SCENE(HIDAN_scene, g_pn_03, SCENE_FIRE_TEMPLE, SDC_FIRE_TEMPLE, 2, 6)
/* 0x05 */ DEFINE_SCENE(MIZUsin_scene, g_pn_04, SCENE_WATER_TEMPLE, SDC_WATER_TEMPLE, 1, 7)
/* 0x06 */ DEFINE_SCENE(jyasinzou_scene, g_pn_05, SCENE_SPIRIT_TEMPLE, SDC_SPIRIT_TEMPLE, 1, 8)
/* 0x07 */ DEFINE_SCENE(HAKAdan_scene, g_pn_02, SCENE_SHADOW_TEMPLE, SDC_SHADOW_TEMPLE_AND_WELL, 2, 9)
/* 0x08 */ DEFINE_SCENE(HAKAdanCH_scene, g_pn_54, SCENE_BOTTOM_OF_THE_WELL, SDC_SHADOW_TEMPLE_AND_WELL, 2, 10)
/* 0x09 */ DEFINE_SCENE(ice_doukutu_scene, g_pn_10, SCENE_ICE_CAVERN, SDC_ICE_CAVERN, 0, 0)
/* 0x0A */ DEFINE_SCENE(ganon_scene, none, SCENE_GANONS_TOWER, SDC_DEFAULT, 2, 0)
/* 0x0B */ DEFINE_SCENE(men_scene, g_pn_11, SCENE_GERUDO_TRAINING_GROUND, SDC_GERUDO_TRAINING_GROUND, 0, 0)
/* 0x0C */ DEFINE_SCENE(gerudoway_scene, g_pn_49, SCENE_THIEVES_HIDEOUT, SDC_THIEVES_HIDEOUT, 0, 0)
/* 0x0D */ DEFINE_SCENE(ganontika_scene, g_pn_09, SCENE_INSIDE_GANONS_CASTLE, SDC_INSIDE_GANONS_CASTLE, 0, 0)
/* 0x0E */ DEFINE_SCENE(ganon_sonogo_scene, none, SCENE_GANONS_TOWER_COLLAPSE_INTERIOR, SDC_GANONS_TOWER_COLLAPSE_INTERIOR, 0, 0)
/* 0x0F */ DEFINE_SCENE(ganontikasonogo_scene, none, SCENE_INSIDE_GANONS_CASTLE_COLLAPSE, SDC_INSIDE_GANONS_CASTLE_COLLAPSE, 0, 0)
/* 0x10 */ DEFINE_SCENE(takaraya_scene, g_pn_51, SCENE_TREASURE_BOX_SHOP, SDC_DEFAULT, 0, 0)
/* 0x11 */ DEFINE_SCENE(ydan_boss_scene, none, SCENE_DEKU_TREE_BOSS, SDC_DEKU_TREE_BOSS, 0, 0)
/* 0x12 */ DEFINE_SCENE(ddan_boss_scene, none, SCENE_DODONGOS_CAVERN_BOSS, SDC_DEFAULT, 0, 0)
/* 0x13 */ DEFINE_SCENE(bdan_boss_scene, none, SCENE_JABU_JABU_BOSS, SDC_JABU_JABU, 0, 0)
/* 0x14 */ DEFINE_SCENE(moribossroom_scene, none, SCENE_FOREST_TEMPLE_BOSS, SDC_DEFAULT, 1, 0)
/* 0x15 */ DEFINE_SCENE(FIRE_bs_scene, none, SCENE_FIRE_TEMPLE_BOSS, SDC_FIRE_TEMPLE, 0, 0)
/* 0x16 */ DEFINE_SCENE(MIZUsin_bs_scene, none, SCENE_WATER_TEMPLE_BOSS, SDC_WATER_TEMPLE_BOSS, 0, 0)
/* 0x17 */ DEFINE_SCENE(jyasinboss_scene, none, SCENE_SPIRIT_TEMPLE_BOSS, SDC_DEFAULT, 0, 0)
/* 0x18 */ DEFINE_SCENE(HAKAdan_bs_scene, none, SCENE_SHADOW_TEMPLE_BOSS, SDC_SHADOW_TEMPLE_AND_WELL, 0, 0)
/* 0x19 */ DEFINE_SCENE(ganon_boss_scene, none, SCENE_GANONDORF_BOSS, SDC_DEFAULT, 0, 0)
/* 0x1A */ DEFINE_SCENE(ganon_final_scene, none, SCENE_GANONS_TOWER_COLLAPSE_EXTERIOR, SDC_GANONS_TOWER_COLLAPSE_EXTERIOR, 0, 0)
/* 0x1B */ DEFINE_SCENE(entra_scene, none, SCENE_MARKET_ENTRANCE_DAY, SDC_DEFAULT, 0, 0)
/* 0x1C */ DEFINE_SCENE(entra_n_scene, none, SCENE_MARKET_ENTRANCE_NIGHT, SDC_DEFAULT, 0, 0)
/* 0x1D */ DEFINE_SCENE(enrui_scene, none, SCENE_MARKET_ENTRANCE_RUINS, SDC_DEFAULT, 0, 0)
/* 0x1E */ DEFINE_SCENE(market_alley_scene, g_pn_18, SCENE_BACK_ALLEY_DAY, SDC_DEFAULT, 0, 0)
/* 0x1F */ DEFINE_SCENE(market_alley_n_scene, g_pn_18, SCENE_BACK_ALLEY_NIGHT, SDC_DEFAULT, 0, 0)
/* 0x20 */ DEFINE_SCENE(market_day_scene, g_pn_17, SCENE_MARKET_DAY, SDC_DEFAULT, 0, 0)
/* 0x21 */ DEFINE_SCENE(market_night_scene, g_pn_17, SCENE_MARKET_NIGHT, SDC_DEFAULT, 0, 0)
/* 0x22 */ DEFINE_SCENE(market_ruins_scene, g_pn_17, SCENE_MARKET_RUINS, SDC_DEFAULT, 0, 0)
/* 0x23 */ DEFINE_SCENE(shrine_scene, none, SCENE_TEMPLE_OF_TIME_EXTERIOR_DAY, SDC_DEFAULT, 0, 0)
/* 0x24 */ DEFINE_SCENE(shrine_n_scene, none, SCENE_TEMPLE_OF_TIME_EXTERIOR_NIGHT, SDC_DEFAULT, 0, 0)
/* 0x25 */ DEFINE_SCENE(shrine_r_scene, none, SCENE_TEMPLE_OF_TIME_EXTERIOR_RUINS, SDC_DEFAULT, 0, 0)
/* 0x26 */ DEFINE_SCENE(kokiri_home_scene, none, SCENE_KNOW_IT_ALL_BROS_HOUSE, SDC_DEFAULT, 0, 0)
/* 0x27 */ DEFINE_SCENE(kokiri_home3_scene, none, SCENE_TWINS_HOUSE, SDC_DEFAULT, 0, 0)
/* 0x28 */ DEFINE_SCENE(kokiri_home4_scene, none, SCENE_MIDOS_HOUSE, SDC_DEFAULT, 0, 0)
/* 0x29 */ DEFINE_SCENE(kokiri_home5_scene, none, SCENE_SARIAS_HOUSE, SDC_DEFAULT, 0, 0)
/* 0x2A */ DEFINE_SCENE(kakariko_scene, none, SCENE_KAKARIKO_CENTER_GUEST_HOUSE, SDC_DEFAULT, 0, 0)
/* 0x2B */ DEFINE_SCENE(kakariko3_scene, none, SCENE_BACK_ALLEY_HOUSE, SDC_DEFAULT, 0, 0)
/* 0x2C */ DEFINE_SCENE(shop1_scene, g_pn_23, SCENE_BAZAAR, SDC_DEFAULT, 0, 0)
/* 0x2D */ DEFINE_SCENE(kokiri_shop_scene, g_pn_19, SCENE_KOKIRI_SHOP, SDC_DEFAULT, 0, 0)
/* 0x2E */ DEFINE_SCENE(golon_scene, g_pn_20, SCENE_GORON_SHOP, SDC_DEFAULT, 0, 0)
/* 0x2F */ DEFINE_SCENE(zoora_scene, g_pn_21, SCENE_ZORA_SHOP, SDC_DEFAULT, 0, 0)
/* 0x30 */ DEFINE_SCENE(drag_scene, g_pn_24, SCENE_POTION_SHOP_KAKARIKO, SDC_DEFAULT, 0, 0)
/* 0x31 */ DEFINE_SCENE(alley_shop_scene, g_pn_24, SCENE_POTION_SHOP_MARKET, SDC_DEFAULT, 0, 0)
/* 0x32 */ DEFINE_SCENE(night_shop_scene, g_pn_56, SCENE_BOMBCHU_SHOP, SDC_DEFAULT, 0, 0)
/* 0x33 */ DEFINE_SCENE(face_shop_scene, g_pn_50, SCENE_HAPPY_MASK_SHOP, SDC_DEFAULT, 0, 0)
/* 0x34 */ DEFINE_SCENE(link_home_scene, none, SCENE_LINKS_HOUSE, SDC_DEFAULT, 0, 0)
/* 0x35 */ DEFINE_SCENE(impa_scene, none, SCENE_DOG_LADY_HOUSE, SDC_DEFAULT, 0, 0)
/* 0x36 */ DEFINE_SCENE(malon_stable_scene, g_pn_48, SCENE_STABLE, SDC_DEFAULT, 0, 0)
/* 0x37 */ DEFINE_SCENE(labo_scene, none, SCENE_IMPAS_HOUSE, SDC_DEFAULT, 0, 0)
/* 0x38 */ DEFINE_SCENE(hylia_labo_scene, g_pn_26, SCENE_LAKESIDE_LABORATORY, SDC_LAKESIDE_LABORATORY, 0, 0)
/* 0x39 */ DEFINE_SCENE(tent_scene, none, SCENE_CARPENTERS_TENT, SDC_DEFAULT, 0, 0)
/* 0x3A */ DEFINE_SCENE(hut_scene, g_pn_25, SCENE_GRAVEKEEPERS_HUT, SDC_DEFAULT, 0, 0)
/* 0x3B */ DEFINE_SCENE(daiyousei_izumi_scene, g_pn_13, SCENE_GREAT_FAIRYS_FOUNTAIN_MAGIC, SDC_GREAT_FAIRYS_FOUNTAIN, 0, 0)
/* 0x3C */ DEFINE_SCENE(yousei_izumi_tate_scene, g_pn_45, SCENE_FAIRYS_FOUNTAIN, SDC_FAIRYS_FOUNTAIN, 0, 0)
/* 0x3D */ DEFINE_SCENE(yousei_izumi_yoko_scene, g_pn_13, SCENE_GREAT_FAIRYS_FOUNTAIN_SPELLS, SDC_GREAT_FAIRYS_FOUNTAIN, 0, 0)
/* 0x3E */ DEFINE_SCENE(kakusiana_scene, none, SCENE_GROTTOS, SDC_GROTTOS, 0, 0)
/* 0x3F */ DEFINE_SCENE(hakaana_scene, none, SCENE_REDEAD_GRAVE, SDC_GRAVE_EXIT_LIGHT_SHINING, 0, 0)
/* 0x40 */ DEFINE_SCENE(hakaana2_scene, none, SCENE_GRAVE_WITH_FAIRYS_FOUNTAIN, SDC_FAIRYS_FOUNTAIN, 0, 0)
/* 0x41 */ DEFINE_SCENE(hakaana_ouke_scene, g_pn_44, SCENE_ROYAL_FAMILYS_TOMB, SDC_ROYAL_FAMILYS_TOMB, 0, 0)
/* 0x42 */ DEFINE_SCENE(syatekijyou_scene, g_pn_15, SCENE_SHOOTING_GALLERY, SDC_SHOOTING_GALLERY, 0, 0)
/* 0x43 */ DEFINE_SCENE(tokinoma_scene, g_pn_16, SCENE_TEMPLE_OF_TIME, SDC_TEMPLE_OF_TIME, 0, 0)
/* 0x44 */ DEFINE_SCENE(kenjyanoma_scene, g_pn_14, SCENE_CHAMBER_OF_THE_SAGES, SDC_CHAMBER_OF_THE_SAGES, 0, 0)
/* 0x45 */ DEFINE_SCENE(hairal_niwa_scene, g_pn_12, SCENE_CASTLE_COURTYARD_GUARDS_DAY, SDC_CASTLE_COURTYARD_GUARDS, 0, 0)
/* 0x46 */ DEFINE_SCENE(hairal_niwa_n_scene, g_pn_12, SCENE_CASTLE_COURTYARD_GUARDS_NIGHT, SDC_CASTLE_COURTYARD_GUARDS, 0, 0)
/* 0x47 */ DEFINE_SCENE(hiral_demo_scene, none, SCENE_CUTSCENE_MAP, SDC_DEFAULT, 0, 0)
/* 0x48 */ DEFINE_SCENE(hakasitarelay_scene, g_pn_57, SCENE_WINDMILL_AND_DAMPES_GRAVE, SDC_GRAVE_EXIT_LIGHT_SHINING, 0, 0)
/* 0x49 */ DEFINE_SCENE(turibori_scene, g_pn_46, SCENE_FISHING_POND, SDC_FISHING_POND, 0, 0)
/* 0x4A */ DEFINE_SCENE(nakaniwa_scene, g_pn_12, SCENE_CASTLE_COURTYARD_ZELDA, SDC_CALM_WATER, 0, 0)
/* 0x4B */ DEFINE_SCENE(bowling_scene, g_pn_47, SCENE_BOMBCHU_BOWLING_ALLEY, SDC_BOMBCHU_BOWLING_ALLEY, 0, 0)
/* 0x4C */ DEFINE_SCENE(souko_scene, none, SCENE_LON_LON_BUILDINGS, SDC_LON_LON_BUILDINGS, 0, 0)
/* 0x4D */ DEFINE_SCENE(miharigoya_scene, none, SCENE_MARKET_GUARD_HOUSE, SDC_MARKET_GUARD_HOUSE, 0, 0)
/* 0x4E */ DEFINE_SCENE(mahouya_scene, g_pn_24, SCENE_POTION_SHOP_GRANNY, SDC_POTION_SHOP_GRANNY, 0, 0)
/* 0x4F */ DEFINE_SCENE(ganon_demo_scene, none, SCENE_GANON_BOSS, SDC_OUTSIDE_GANONS_CASTLE, 0, 0)
/* 0x50 */ DEFINE_SCENE(kinsuta_scene, g_pn_22, SCENE_HOUSE_OF_SKULLTULA, SDC_DEFAULT, 0, 0)
/* 0x51 */ DEFINE_SCENE(spot00_scene, g_pn_27, SCENE_HYRULE_FIELD, SDC_HYRULE_FIELD, 0, 0)
/* 0x52 */ DEFINE_SCENE(spot01_scene, g_pn_28, SCENE_KAKARIKO_VILLAGE, SDC_KAKARIKO_VILLAGE, 0, 0)
/* 0x53 */ DEFINE_SCENE(spot02_scene, g_pn_29, SCENE_GRAVEYARD, SDC_DEFAULT, 0, 0)
/* 0x54 */ DEFINE_SCENE(spot03_scene, g_pn_30, SCENE_ZORAS_RIVER, SDC_ZORAS_RIVER, 0, 0)
/* 0x55 */ DEFINE_SCENE(spot04_scene, g_pn_31, SCENE_KOKIRI_FOREST, SDC_KOKIRI_FOREST, 0, 0)
/* 0x56 */ DEFINE_SCENE(spot05_scene, g_pn_52, SCENE_SACRED_FOREST_MEADOW, SDC_CALM_WATER, 0, 0)
/* 0x57 */ DEFINE_SCENE(spot06_scene, g_pn_32, SCENE_LAKE_HYLIA, SDC_LAKE_HYLIA, 0, 0)
/* 0x58 */ DEFINE_SCENE(spot07_scene, g_pn_33, SCENE_ZORAS_DOMAIN, SDC_ZORAS_DOMAIN, 0, 0)
/* 0x59 */ DEFINE_SCENE(spot08_scene, g_pn_34, SCENE_ZORAS_FOUNTAIN, SDC_ZORAS_FOUNTAIN, 0, 0)
/* 0x5A */ DEFINE_SCENE(spot09_scene, g_pn_35, SCENE_GERUDO_VALLEY, SDC_GERUDO_VALLEY, 0, 0)
/* 0x5B */ DEFINE_SCENE(spot10_scene, g_pn_36, SCENE_LOST_WOODS, SDC_LOST_WOODS, 0, 0)
/* 0x5C */ DEFINE_SCENE(spot11_scene, g_pn_55, SCENE_DESERT_COLOSSUS, SDC_DESERT_COLOSSUS, 0, 0)
/* 0x5D */ DEFINE_SCENE(spot12_scene, g_pn_53, SCENE_GERUDOS_FORTRESS, SDC_GERUDOS_FORTRESS, 0, 0)
/* 0x5E */ DEFINE_SCENE(spot13_scene, g_pn_37, SCENE_HAUNTED_WASTELAND, SDC_HAUNTED_WASTELAND, 0, 0)
/* 0x5F */ DEFINE_SCENE(spot15_scene, g_pn_38, SCENE_HYRULE_CASTLE, SDC_HYRULE_CASTLE, 0, 0)
/* 0x60 */ DEFINE_SCENE(spot16_scene, g_pn_39, SCENE_DEATH_MOUNTAIN_TRAIL, SDC_DEATH_MOUNTAIN_TRAIL, 0, 0)
/* 0x61 */ DEFINE_SCENE(spot17_scene, g_pn_40, SCENE_DEATH_MOUNTAIN_CRATER, SDC_DEATH_MOUNTAIN_CRATER, 0, 0)
/* 0x62 */ DEFINE_SCENE(spot18_scene, g_pn_41, SCENE_GORON_CITY, SDC_GORON_CITY, 0, 0)
/* 0x63 */ DEFINE_SCENE(spot20_scene, g_pn_42, SCENE_LON_LON_RANCH, SDC_LON_LON_RANCH, 0, 0)
/* 0x64 */ DEFINE_SCENE(ganon_tou_scene, g_pn_43, SCENE_OUTSIDE_GANONS_CASTLE, SDC_OUTSIDE_GANONS_CASTLE, 0, 0)
// Debug-only scenes
/* 0x65 */ DEFINE_SCENE(test01_scene, none, SCENE_TEST01, SDC_CALM_WATER, 0, 0)
/* 0x66 */ DEFINE_SCENE(besitu_scene, none, SCENE_BESITU, SDC_BESITU, 0, 0)
/* 0x67 */ DEFINE_SCENE(depth_test_scene, none, SCENE_DEPTH_TEST, SDC_DEFAULT, 0, 0)
/* 0x68 */ DEFINE_SCENE(syotes_scene, none, SCENE_SYOTES, SDC_DEFAULT, 0, 0)
/* 0x69 */ DEFINE_SCENE(syotes2_scene, none, SCENE_SYOTES2, SDC_DEFAULT, 0, 0)
/* 0x6A */ DEFINE_SCENE(sutaru_scene, none, SCENE_SUTARU, SDC_DEFAULT, 0, 0)
/* 0x6B */ DEFINE_SCENE(hairal_niwa2_scene, g_pn_12, SCENE_HAIRAL_NIWA2, SDC_CASTLE_COURTYARD_GUARDS, 0, 0)
/* 0x6C */ DEFINE_SCENE(sasatest_scene, none, SCENE_SASATEST, SDC_DEFAULT, 0, 0)
/* 0x6D */ DEFINE_SCENE(testroom_scene, none, SCENE_TESTROOM, SDC_DEFAULT, 0, 0)
// Added scenes
/* 0x6E */ DEFINE_SCENE(test_room_scene, none, SCENE_TEST_ROOM, SDC_ROYAL_FAMILYS_TOMB, 0, 0)
/* 0x6E */ DEFINE_SCENE(test_valley_scene, g_pn_29, SCENE_TEST_VALLEY, SDC_DEFAULT, 0, 0)
/* 0x6E */ DEFINE_SCENE(sand_room_scene, g_pn_29, SCENE_SAND_ROOM, SDC_DEFAULT, 0, 0)
/* 0x6E */ DEFINE_SCENE(milk_ranch_scene, g_pn_29, SCENE_MILK_RANCH, SDC_DEFAULT, 0, 0)
/* 0x6E */ DEFINE_SCENE(starting_depths_scene, g_pn_29, SCENE_STARTING_DEPTHS, SDC_DEFAULT, 0, 0)
