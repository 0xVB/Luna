#pragma once

enum ReanimationID { REANIMID_NULL };
enum PlantID { PLANTID_NULL };
enum ZombieID { ZOMBIEID_NULL };
enum AttachmentID { ATTACHMENTID_NULL };
enum ParticleSystemID { PARTICLESYSTEMID_NULL };

enum CrazyDaveState
{
	CRAZY_DAVE_OFF = 0x0,
	CRAZY_DAVE_ENTERING = 0x1,
	CRAZY_DAVE_LEAVING = 0x2,
	CRAZY_DAVE_IDLING = 0x3,
	CRAZY_DAVE_TALKING = 0x4,
	CRAZY_DAVE_HANDING_TALKING = 0x5,
	CRAZY_DAVE_HANDING_IDLING = 0x6,
};
enum GameMode
{
	GAMEMODE_ADVENTURE = 0x0,
	GAMEMODE_SURVIVAL_NORMAL_STAGE_1 = 0x1,
	GAMEMODE_SURVIVAL_NORMAL_STAGE_2 = 0x2,
	GAMEMODE_SURVIVAL_NORMAL_STAGE_3 = 0x3,
	GAMEMODE_SURVIVAL_NORMAL_STAGE_4 = 0x4,
	GAMEMODE_SURVIVAL_NORMAL_STAGE_5 = 0x5,
	GAMEMODE_SURVIVAL_HARD_STAGE_1 = 0x6,
	GAMEMODE_SURVIVAL_HARD_STAGE_2 = 0x7,
	GAMEMODE_SURVIVAL_HARD_STAGE_3 = 0x8,
	GAMEMODE_SURVIVAL_HARD_STAGE_4 = 0x9,
	GAMEMODE_SURVIVAL_HARD_STAGE_5 = 0xA,
	GAMEMODE_SURVIVAL_ENDLESS_STAGE_1 = 0xB,
	GAMEMODE_SURVIVAL_ENDLESS_STAGE_2 = 0xC,
	GAMEMODE_SURVIVAL_ENDLESS_STAGE_3 = 0xD,
	GAMEMODE_SURVIVAL_ENDLESS_STAGE_4 = 0xE,
	GAMEMODE_SURVIVAL_ENDLESS_STAGE_5 = 0xF,
	GAMEMODE_CHALLENGE_WAR_AND_PEAS = 0x10,
	GAMEMODE_CHALLENGE_WALLNUT_BOWLING = 0x11,
	GAMEMODE_CHALLENGE_SLOT_MACHINE = 0x12,
	GAMEMODE_CHALLENGE_RAINING_SEEDS = 0x13,
	GAMEMODE_CHALLENGE_BEGHOULED = 0x14,
	GAMEMODE_CHALLENGE_INVISIGHOUL = 0x15,
	GAMEMODE_CHALLENGE_SEEING_STARS = 0x16,
	GAMEMODE_CHALLENGE_ZOMBIQUARIUM = 0x17,
	GAMEMODE_CHALLENGE_BEGHOULED_TWIST = 0x18,
	GAMEMODE_CHALLENGE_LITTLE_TROUBLE = 0x19,
	GAMEMODE_CHALLENGE_PORTAL_COMBAT = 0x1A,
	GAMEMODE_CHALLENGE_COLUMN = 0x1B,
	GAMEMODE_CHALLENGE_BOBSLED_BONANZA = 0x1C,
	GAMEMODE_CHALLENGE_SPEED = 0x1D,
	GAMEMODE_CHALLENGE_WHACK_A_ZOMBIE = 0x1E,
	GAMEMODE_CHALLENGE_LAST_STAND = 0x1F,
	GAMEMODE_CHALLENGE_WAR_AND_PEAS_2 = 0x20,
	GAMEMODE_CHALLENGE_WALLNUT_BOWLING_2 = 0x21,
	GAMEMODE_CHALLENGE_POGO_PARTY = 0x22,
	GAMEMODE_CHALLENGE_FINAL_BOSS = 0x23,
	GAMEMODE_CHALLENGE_ART_CHALLENGE_1 = 0x24,
	GAMEMODE_CHALLENGE_SUNNY_DAY = 0x25,
	GAMEMODE_CHALLENGE_RESODDED = 0x26,
	GAMEMODE_CHALLENGE_BIG_TIME = 0x27,
	GAMEMODE_CHALLENGE_ART_CHALLENGE_2 = 0x28,
	GAMEMODE_CHALLENGE_AIR_RAID = 0x29,
	GAMEMODE_CHALLENGE_ICE = 0x2A,
	GAMEMODE_CHALLENGE_ZEN_GARDEN = 0x2B,
	GAMEMODE_CHALLENGE_HIGH_GRAVITY = 0x2C,
	GAMEMODE_CHALLENGE_GRAVE_DANGER = 0x2D,
	GAMEMODE_CHALLENGE_SHOVEL = 0x2E,
	GAMEMODE_CHALLENGE_STORMY_NIGHT = 0x2F,
	GAMEMODE_CHALLENGE_BUNGEE_BLITZ = 0x30,
	GAMEMODE_CHALLENGE_SQUIRREL = 0x31,
	GAMEMODE_TREE_OF_WISDOM = 0x32,
	GAMEMODE_SCARY_POTTER_1 = 0x33,
	GAMEMODE_SCARY_POTTER_2 = 0x34,
	GAMEMODE_SCARY_POTTER_3 = 0x35,
	GAMEMODE_SCARY_POTTER_4 = 0x36,
	GAMEMODE_SCARY_POTTER_5 = 0x37,
	GAMEMODE_SCARY_POTTER_6 = 0x38,
	GAMEMODE_SCARY_POTTER_7 = 0x39,
	GAMEMODE_SCARY_POTTER_8 = 0x3A,
	GAMEMODE_SCARY_POTTER_9 = 0x3B,
	GAMEMODE_SCARY_POTTER_ENDLESS = 0x3C,
	GAMEMODE_PUZZLE_I_ZOMBIE_1 = 0x3D,
	GAMEMODE_PUZZLE_I_ZOMBIE_2 = 0x3E,
	GAMEMODE_PUZZLE_I_ZOMBIE_3 = 0x3F,
	GAMEMODE_PUZZLE_I_ZOMBIE_4 = 0x40,
	GAMEMODE_PUZZLE_I_ZOMBIE_5 = 0x41,
	GAMEMODE_PUZZLE_I_ZOMBIE_6 = 0x42,
	GAMEMODE_PUZZLE_I_ZOMBIE_7 = 0x43,
	GAMEMODE_PUZZLE_I_ZOMBIE_8 = 0x44,
	GAMEMODE_PUZZLE_I_ZOMBIE_9 = 0x45,
	GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS = 0x46,
	NUM_GAME_MODES = 0x47,
};
enum GameScenes
{
	SCENE_LOADING = 0x0,
	SCENE_MENU = 0x1,
	SCENE_LEVEL_INTRO = 0x2,
	SCENE_PLAYING = 0x3,
	SCENE_ZOMBIES_WON = 0x4,
	SCENE_AWARD = 0x5,
	SCENE_CREDIT = 0x6,
	SCENE_CHALLENGE = 0x7,
};
enum GameResult
{
	GAMERESULT_NONE = 0x0,
	GAMERESULT_WON = 0x1,
	GAMERESULT_LOST = 0x2,
	GAMERESULT_RESTART = 0x3,
	GAMERESULT_QUIT = 0x4,
	GAMERESULT_QUIT_APP = 0x5,
	GAMERESULT_CHEAT = 0x6,
};
enum ParticleEffect
{
	PARTICLE_NONE = 0xFFFFFFFF,
	PARTICLE_MELONSPLASH = 0x0,
	PARTICLE_WINTERMELON = 0x1,
	PARTICLE_FUMECLOUD = 0x2,
	PARTICLE_POPCORNSPLASH = 0x3,
	PARTICLE_POWIE = 0x4,
	PARTICLE_JACKEXPLODE = 0x5,
	PARTICLE_ZOMBIE_HEAD = 0x6,
	PARTICLE_ZOMBIE_ARM = 0x7,
	PARTICLE_ZOMBIE_TRAFFIC_CONE = 0x8,
	PARTICLE_ZOMBIE_PAIL = 0x9,
	PARTICLE_ZOMBIE_HELMET = 0xA,
	PARTICLE_ZOMBIE_FLAG = 0xB,
	PARTICLE_ZOMBIE_DOOR = 0xC,
	PARTICLE_ZOMBIE_NEWSPAPER = 0xD,
	PARTICLE_ZOMBIE_HEADLIGHT = 0xE,
	PARTICLE_POW = 0xF,
	PARTICLE_ZOMBIE_POGO = 0x10,
	PARTICLE_ZOMBIE_NEWSPAPER_HEAD = 0x11,
	PARTICLE_ZOMBIE_BALLOON_HEAD = 0x12,
	PARTICLE_SOD_ROLL = 0x13,
	PARTICLE_GRAVE_STONE_RISE = 0x14,
	PARTICLE_PLANTING = 0x15,
	PARTICLE_PLANTING_POOL = 0x16,
	PARTICLE_ZOMBIE_RISE = 0x17,
	PARTICLE_GRAVE_BUSTER = 0x18,
	PARTICLE_GRAVE_BUSTER_DIE = 0x19,
	PARTICLE_POOL_SPLASH = 0x1A,
	PARTICLE_ICE_SPARKLE = 0x1B,
	PARTICLE_SEED_PACKET = 0x1C,
	PARTICLE_TALL_NUT_BLOCK = 0x1D,
	PARTICLE_DOOM = 0x1E,
	PARTICLE_DIGGER_RISE = 0x1F,
	PARTICLE_DIGGER_TUNNEL = 0x20,
	PARTICLE_DANCER_RISE = 0x21,
	PARTICLE_POOL_SPARKLY = 0x22,
	PARTICLE_WALLNUT_EAT_SMALL = 0x23,
	PARTICLE_WALLNUT_EAT_LARGE = 0x24,
	PARTICLE_PEA_SPLAT = 0x25,
	PARTICLE_SPIKE_SPLAT = 0x26,
	PARTICLE_BUTTER_SPLAT = 0x27,
	PARTICLE_CABBAGE_SPLAT = 0x28,
	PARTICLE_PUFF_SPLAT = 0x29,
	PARTICLE_STAR_SPLAT = 0x2A,
	PARTICLE_ICE_TRAP = 0x2B,
	PARTICLE_SNOWPEA_SPLAT = 0x2C,
	PARTICLE_SNOWPEA_PUFF = 0x2D,
	PARTICLE_SNOWPEA_TRAIL = 0x2E,
	PARTICLE_LANTERN_SHINE = 0x2F,
	PARTICLE_SEED_PACKET_PICKUP = 0x30,
	PARTICLE_POTATO_MINE = 0x31,
	PARTICLE_POTATO_MINE_RISE = 0x32,
	PARTICLE_PUFFSHROOM_TRAIL = 0x33,
	PARTICLE_PUFFSHROOM_MUZZLE = 0x34,
	PARTICLE_SEED_PACKET_FLASH = 0x35,
	PARTICLE_WHACK_A_ZOMBIE_RISE = 0x36,
	PARTICLE_ZOMBIE_LADDER = 0x37,
	PARTICLE_UMBRELLA_REFLECT = 0x38,
	PARTICLE_SEED_PACKET_PICK = 0x39,
	PARTICLE_ICE_TRAP_ZOMBIE = 0x3A,
	PARTICLE_ICE_TRAP_RELEASE = 0x3B,
	PARTICLE_ZAMBONI_SMOKE = 0x3C,
	PARTICLE_GLOOMCLOUD = 0x3D,
	PARTICLE_ZOMBIE_POGO_HEAD = 0x3E,
	PARTICLE_ZAMBONI_TIRE = 0x3F,
	PARTICLE_ZAMBONI_EXPLOSION = 0x40,
	PARTICLE_ZAMBONI_EXPLOSION2 = 0x41,
	PARTICLE_CATAPULT_EXPLOSION = 0x42,
	PARTICLE_MOWER_CLOUD = 0x43,
	PARTICLE_BOSS_ICE_BALL = 0x44,
	PARTICLE_BLASTMARK = 0x45,
	PARTICLE_COIN_PICKUP_ARROW = 0x46,
	PARTICLE_PRESENT_PICKUP = 0x47,
	PARTICLE_IMITATER_MORPH = 0x48,
	PARTICLE_MOWERED_ZOMBIE_HEAD = 0x49,
	PARTICLE_MOWERED_ZOMBIE_ARM = 0x4A,
	PARTICLE_ZOMBIE_HEAD_POOL = 0x4B,
	PARTICLE_ZOMBIE_BOSS_FIREBALL = 0x4C,
	PARTICLE_FIREBALL_DEATH = 0x4D,
	PARTICLE_ICEBALL_DEATH = 0x4E,
	PARTICLE_ICEBALL_TRAIL = 0x4F,
	PARTICLE_FIREBALL_TRAIL = 0x50,
	PARTICLE_BOSS_EXPLOSION = 0x51,
	PARTICLE_SCREEN_FLASH = 0x52,
	PARTICLE_TROPHY_SPARKLE = 0x53,
	PARTICLE_PORTAL_CIRCLE = 0x54,
	PARTICLE_PORTAL_SQUARE = 0x55,
	PARTICLE_POTTED_PLANT_GLOW = 0x56,
	PARTICLE_POTTED_WATER_PLANT_GLOW = 0x57,
	PARTICLE_POTTED_ZEN_GLOW = 0x58,
	PARTICLE_MIND_CONTROL = 0x59,
	PARTICLE_VASE_SHATTER = 0x5A,
	PARTICLE_VASE_SHATTER_LEAF = 0x5B,
	PARTICLE_VASE_SHATTER_ZOMBIE = 0x5C,
	PARTICLE_AWARD_PICKUP_ARROW = 0x5D,
	PARTICLE_ZOMBIE_SEAWEED = 0x5E,
	PARTICLE_ZOMBIE_MUSTACHE = 0x5F,
	PARTICLE_ZOMBIE_FUTURE_GLASSES = 0x60,
	PARTICLE_PINATA = 0x61,
	PARTICLE_DUST_SQUASH = 0x62,
	PARTICLE_DUST_FOOT = 0x63,
	PARTICLE_DAISY = 0x64,
	PARTICLE_CREDIT_STROBE = 0x65,
	PARTICLE_CREDITS_RAYSWIPE = 0x66,
	PARTICLE_CREDITS_ZOMBIEHEADWIPE = 0x67,
	PARTICLE_STARBURST = 0x68,
	PARTICLE_CREDITS_FOG = 0x69,
	NUM_PARTICLES = 0x6A,
};
enum ReanimationType
{
	REANIM_NONE = 0xFFFFFFFF,
	REANIM_LOADBAR_SPROUT = 0x0,
	REANIM_LOADBAR_ZOMBIEHEAD = 0x1,
	REANIM_SODROLL = 0x2,
	REANIM_FINAL_WAVE = 0x3,
	REANIM_PEASHOOTER = 0x4,
	REANIM_WALLNUT = 0x5,
	REANIM_LILYPAD = 0x6,
	REANIM_SUNFLOWER = 0x7,
	REANIM_LAWNMOWER = 0x8,
	REANIM_READYSETPLANT = 0x9,
	REANIM_CHERRYBOMB = 0xA,
	REANIM_SQUASH = 0xB,
	REANIM_DOOMSHROOM = 0xC,
	REANIM_SNOWPEA = 0xD,
	REANIM_REPEATER = 0xE,
	REANIM_SUNSHROOM = 0xF,
	REANIM_TALLNUT = 0x10,
	REANIM_FUMESHROOM = 0x11,
	REANIM_PUFFSHROOM = 0x12,
	REANIM_HYPNOSHROOM = 0x13,
	REANIM_CHOMPER = 0x14,
	REANIM_ZOMBIE = 0x15,
	REANIM_SUN = 0x16,
	REANIM_POTATOMINE = 0x17,
	REANIM_SPIKEWEED = 0x18,
	REANIM_SPIKEROCK = 0x19,
	REANIM_THREEPEATER = 0x1A,
	REANIM_MARIGOLD = 0x1B,
	REANIM_ICESHROOM = 0x1C,
	REANIM_ZOMBIE_FOOTBALL = 0x1D,
	REANIM_ZOMBIE_NEWSPAPER = 0x1E,
	REANIM_ZOMBIE_ZAMBONI = 0x1F,
	REANIM_SPLASH = 0x20,
	REANIM_JALAPENO = 0x21,
	REANIM_JALAPENO_FIRE = 0x22,
	REANIM_COIN_SILVER = 0x23,
	REANIM_ZOMBIE_CHARRED = 0x24,
	REANIM_ZOMBIE_CHARRED_IMP = 0x25,
	REANIM_ZOMBIE_CHARRED_DIGGER = 0x26,
	REANIM_ZOMBIE_CHARRED_ZAMBONI = 0x27,
	REANIM_ZOMBIE_CHARRED_CATAPULT = 0x28,
	REANIM_ZOMBIE_CHARRED_GARGANTUAR = 0x29,
	REANIM_SCRAREYSHROOM = 0x2A,
	REANIM_PUMPKIN = 0x2B,
	REANIM_PLANTERN = 0x2C,
	REANIM_TORCHWOOD = 0x2D,
	REANIM_SPLITPEA = 0x2E,
	REANIM_SEASHROOM = 0x2F,
	REANIM_BLOVER = 0x30,
	REANIM_FLOWER_POT = 0x31,
	REANIM_CACTUS = 0x32,
	REANIM_DANCER = 0x33,
	REANIM_TANGLEKELP = 0x34,
	REANIM_STARFRUIT = 0x35,
	REANIM_POLEVAULTER = 0x36,
	REANIM_BALLOON = 0x37,
	REANIM_GARGANTUAR = 0x38,
	REANIM_IMP = 0x39,
	REANIM_DIGGER = 0x3A,
	REANIM_DIGGER_DIRT = 0x3B,
	REANIM_ZOMBIE_DOLPHINRIDER = 0x3C,
	REANIM_POGO = 0x3D,
	REANIM_BACKUP_DANCER = 0x3E,
	REANIM_BOBSLED = 0x3F,
	REANIM_JACKINTHEBOX = 0x40,
	REANIM_SNORKEL = 0x41,
	REANIM_BUNGEE = 0x42,
	REANIM_CATAPULT = 0x43,
	REANIM_LADDER = 0x44,
	REANIM_PUFF = 0x45,
	REANIM_SLEEPING = 0x46,
	REANIM_GRAVE_BUSTER = 0x47,
	REANIM_ZOMBIES_WON = 0x48,
	REANIM_MAGNETSHROOM = 0x49,
	REANIM_BOSS = 0x4A,
	REANIM_CABBAGEPULT = 0x4B,
	REANIM_KERNELPULT = 0x4C,
	REANIM_MELONPULT = 0x4D,
	REANIM_COFFEEBEAN = 0x4E,
	REANIM_UMBRELLALEAF = 0x4F,
	REANIM_GATLINGPEA = 0x50,
	REANIM_CATTAIL = 0x51,
	REANIM_GLOOMSHROOM = 0x52,
	REANIM_BOSS_ICEBALL = 0x53,
	REANIM_BOSS_FIREBALL = 0x54,
	REANIM_COBCANNON = 0x55,
	REANIM_GARLIC = 0x56,
	REANIM_GOLD_MAGNET = 0x57,
	REANIM_WINTER_MELON = 0x58,
	REANIM_TWIN_SUNFLOWER = 0x59,
	REANIM_POOL_CLEANER = 0x5A,
	REANIM_ROOF_CLEANER = 0x5B,
	REANIM_FIRE_PEA = 0x5C,
	REANIM_IMITATER = 0x5D,
	REANIM_YETI = 0x5E,
	REANIM_BOSS_DRIVER = 0x5F,
	REANIM_LAWN_MOWERED_ZOMBIE = 0x60,
	REANIM_CRAZY_DAVE = 0x61,
	REANIM_TEXT_FADE_ON = 0x62,
	REANIM_HAMMER = 0x63,
	REANIM_SLOT_MACHINE_HANDLE = 0x64,
	REANIM_CREDITS_FOOTBALL = 0x65,
	REANIM_CREDITS_JACKBOX = 0x66,
	REANIM_SELECTOR_SCREEN = 0x67,
	REANIM_PORTAL_CIRCLE = 0x68,
	REANIM_PORTAL_SQUARE = 0x69,
	REANIM_ZENGARDEN_SPROUT = 0x6A,
	REANIM_ZENGARDEN_WATERINGCAN = 0x6B,
	REANIM_ZENGARDEN_FERTILIZER = 0x6C,
	REANIM_ZENGARDEN_BUGSPRAY = 0x6D,
	REANIM_ZENGARDEN_PHONOGRAPH = 0x6E,
	REANIM_DIAMOND = 0x6F,
	REANIM_ZOMBIE_HAND = 0x70,
	REANIM_STINKY = 0x71,
	REANIM_RAKE = 0x72,
	REANIM_RAIN_CIRCLE = 0x73,
	REANIM_RAIN_SPLASH = 0x74,
	REANIM_ZOMBIE_SURPRISE = 0x75,
	REANIM_COIN_GOLD = 0x76,
	REANIM_TREE_OF_WISDOM = 0x77,
	REANIM_TREE_OF_WISDOM_CLOUDS = 0x78,
	REANIM_TREE_FOOD = 0x79,
	REANIM_CREDITS_MAIN = 0x7A,
	REANIM_CREDITS_MAIN2 = 0x7B,
	REANIM_CREDITS_MAIN3 = 0x7C,
	REANIM_ZOMBIE_CREDITS_DANCE = 0x7D,
	REANIM_CREDITS_STAGE = 0x7E,
	REANIM_CREDITS_BIGBRAIN = 0x7F,
	REANIM_CREDITS_FLOWER_PETALS = 0x80,
	REANIM_CREDITS_INFANTRY = 0x81,
	REANIM_CREDITS_THROAT = 0x82,
	REANIM_CREDITS_CRAZYDAVE = 0x83,
	REANIM_CREDITS_BOSSDANCE = 0x84,
	REANIM_ZOMBIE_CREDITS_SCREEN_DOOR = 0x85,
	REANIM_ZOMBIE_CREDITS_CONEHEAD = 0x86,
	REANIM_CREDITS_ZOMBIEARMY1 = 0x87,
	REANIM_CREDITS_ZOMBIEARMY2 = 0x88,
	REANIM_CREDITS_TOMBSTONES = 0x89,
	REANIM_CREDITS_SOLARPOWER = 0x8A,
	REANIM_CREDITS_ANYHOUR = 0x8B,
	REANIM_CREDITS_WEARETHEUNDEAD = 0x8C,
	REANIM_CREDITS_DISCOLIGHTS = 0x8D,
	NUM_REANIMS = 0x8E,
};
enum GameObjectType
{
	OBJECT_TYPE_NONE = 0x0,
	OBJECT_TYPE_PLANT = 0x1,
	OBJECT_TYPE_PROJECTILE = 0x2,
	OBJECT_TYPE_COIN = 0x3,
	OBJECT_TYPE_SEEDPACKET = 0x4,
	OBJECT_TYPE_SHOVEL = 0x5,
	OBJECT_TYPE_WATERING_CAN = 0x6,
	OBJECT_TYPE_FERTILIZER = 0x7,
	OBJECT_TYPE_BUG_SPRAY = 0x8,
	OBJECT_TYPE_PHONOGRAPH = 0x9,
	OBJECT_TYPE_CHOCOLATE = 0xA,
	OBJECT_TYPE_GLOVE = 0xB,
	OBJECT_TYPE_MONEY_SIGN = 0xC,
	OBJECT_TYPE_WHEELBARROW = 0xD,
	OBJECT_TYPE_TREE_FOOD = 0xE,
	OBJECT_TYPE_NEXT_GARDEN = 0xF,
	OBJECT_TYPE_MENU_BUTTON = 0x10,
	OBJECT_TYPE_STORE_BUTTON = 0x11,
	OBJECT_TYPE_SLOT_MACHINE_HANDLE = 0x12,
	OBJECT_TYPE_SCARY_POT = 0x13,
	OBJECT_TYPE_STINKY = 0x14,
	OBJECT_TYPE_TREE_OF_WISDOM = 0x15,
};
enum HelmType
{
	HELMTYPE_NONE = 0x0,
	HELMTYPE_TRAFFIC_CONE = 0x1,
	HELMTYPE_PAIL = 0x2,
	HELMTYPE_FOOTBALL = 0x3,
	HELMTYPE_DIGGER = 0x4,
	HELMTYPE_REDEYES = 0x5,
	HELMTYPE_HEADBAND = 0x6,
	HELMTYPE_BOBSLED = 0x7,
	HELMTYPE_WALLNUT = 0x8,
	HELMTYPE_TALLNUT = 0x9,
};
enum ZombieType
{
	ZOMBIE_INVALID = 0xFFFFFFFF,
	ZOMBIE_NORMAL = 0x0,
	ZOMBIE_FLAG = 0x1,
	ZOMBIE_TRAFFIC_CONE = 0x2,
	ZOMBIE_POLEVAULTER = 0x3,
	ZOMBIE_PAIL = 0x4,
	ZOMBIE_NEWSPAPER = 0x5,
	ZOMBIE_DOOR = 0x6,
	ZOMBIE_FOOTBALL = 0x7,
	ZOMBIE_DANCER = 0x8,
	ZOMBIE_BACKUP_DANCER = 0x9,
	ZOMBIE_DUCKY_TUBE = 0xA,
	ZOMBIE_SNORKEL = 0xB,
	ZOMBIE_ZAMBONI = 0xC,
	ZOMBIE_BOBSLED = 0xD,
	ZOMBIE_DOLPHIN_RIDER = 0xE,
	ZOMBIE_JACK_IN_THE_BOX = 0xF,
	ZOMBIE_BALLOON = 0x10,
	ZOMBIE_DIGGER = 0x11,
	ZOMBIE_POGO = 0x12,
	ZOMBIE_YETI = 0x13,
	ZOMBIE_BUNGEE = 0x14,
	ZOMBIE_LADDER = 0x15,
	ZOMBIE_CATAPULT = 0x16,
	ZOMBIE_GARGANTUAR = 0x17,
	ZOMBIE_IMP = 0x18,
	ZOMBIE_BOSS = 0x19,
	ZOMBIE_PEA_HEAD = 0x1A,
	ZOMBIE_WALLNUT_HEAD = 0x1B,
	ZOMBIE_JALAPENO_HEAD = 0x1C,
	ZOMBIE_GATLING_HEAD = 0x1D,
	ZOMBIE_SQUASH_HEAD = 0x1E,
	ZOMBIE_TALLNUT_HEAD = 0x1F,
	ZOMBIE_REDEYE_GARGANTUAR = 0x20,
	NUM_ZOMBIE_TYPES = 0x21,
	BASE_NUM_ZOMBIE_TYPES = 0x21,
};
enum ZombiePhase
{
	PHASE_ZOMBIE_NORMAL = 0x0,
	PHASE_ZOMBIE_DYING = 0x1,
	PHASE_ZOMBIE_BURNED = 0x2,
	PHASE_ZOMBIE_MOWERED = 0x3,
	PHASE_BUNGEE_DIVING = 0x4,
	PHASE_BUNGEE_DIVING_SCREAMING = 0x5,
	PHASE_BUNGEE_AT_BOTTOM = 0x6,
	PHASE_BUNGEE_GRABBING = 0x7,
	PHASE_BUNGEE_RISING = 0x8,
	PHASE_BUNGEE_HIT_OUCHY = 0x9,
	PHASE_BUNGEE_CUTSCENE = 0xA,
	PHASE_POLEVAULTER_PRE_VAULT = 0xB,
	PHASE_POLEVAULTER_IN_VAULT = 0xC,
	PHASE_POLEVAULTER_POST_VAULT = 0xD,
	PHASE_RISING_FROM_GRAVE = 0xE,
	PHASE_JACK_IN_THE_BOX_RUNNING = 0xF,
	PHASE_JACK_IN_THE_BOX_POPPING = 0x10,
	PHASE_BOBSLED_SLIDING = 0x11,
	PHASE_BOBSLED_BOARDING = 0x12,
	PHASE_BOBSLED_CRASHING = 0x13,
	PHASE_POGO_BOUNCING = 0x14,
	PHASE_POGO_HIGH_BOUNCE_1 = 0x15,
	PHASE_POGO_HIGH_BOUNCE_2 = 0x16,
	PHASE_POGO_HIGH_BOUNCE_3 = 0x17,
	PHASE_POGO_HIGH_BOUNCE_4 = 0x18,
	PHASE_POGO_HIGH_BOUNCE_5 = 0x19,
	PHASE_POGO_HIGH_BOUNCE_6 = 0x1A,
	PHASE_POGO_FORWARD_BOUNCE_2 = 0x1B,
	PHASE_POGO_FORWARD_BOUNCE_7 = 0x1C,
	PHASE_NEWSPAPER_READING = 0x1D,
	PHASE_NEWSPAPER_MADDENING = 0x1E,
	PHASE_NEWSPAPER_MAD = 0x1F,
	PHASE_DIGGER_TUNNELING = 0x20,
	PHASE_DIGGER_RISING = 0x21,
	PHASE_DIGGER_TUNNELING_PAUSE_WITHOUT_AXE = 0x22,
	PHASE_DIGGER_RISE_WITHOUT_AXE = 0x23,
	PHASE_DIGGER_STUNNED = 0x24,
	PHASE_DIGGER_WALKING = 0x25,
	PHASE_DIGGER_WALKING_WITHOUT_AXE = 0x26,
	PHASE_DIGGER_CUTSCENE = 0x27,
	PHASE_DANCER_DANCING_IN = 0x28,
	PHASE_DANCER_SNAPPING_FINGERS = 0x29,
	PHASE_DANCER_SNAPPING_FINGERS_WITH_LIGHT = 0x2A,
	PHASE_DANCER_SNAPPING_FINGERS_HOLD = 0x2B,
	PHASE_DANCER_DANCING_LEFT = 0x2C,
	PHASE_DANCER_WALK_TO_RAISE = 0x2D,
	PHASE_DANCER_RAISE_LEFT_1 = 0x2E,
	PHASE_DANCER_RAISE_RIGHT_1 = 0x2F,
	PHASE_DANCER_RAISE_LEFT_2 = 0x30,
	PHASE_DANCER_RAISE_RIGHT_2 = 0x31,
	PHASE_DANCER_RISING = 0x32,
	PHASE_DOLPHIN_WALKING = 0x33,
	PHASE_DOLPHIN_INTO_POOL = 0x34,
	PHASE_DOLPHIN_RIDING = 0x35,
	PHASE_DOLPHIN_IN_JUMP = 0x36,
	PHASE_DOLPHIN_WALKING_IN_POOL = 0x37,
	PHASE_DOLPHIN_WALKING_WITHOUT_DOLPHIN = 0x38,
	PHASE_SNORKEL_WALKING = 0x39,
	PHASE_SNORKEL_INTO_POOL = 0x3A,
	PHASE_SNORKEL_WALKING_IN_POOL = 0x3B,
	PHASE_SNORKEL_UP_TO_EAT = 0x3C,
	PHASE_SNORKEL_EATING_IN_POOL = 0x3D,
	PHASE_SNORKEL_DOWN_FROM_EAT = 0x3E,
	PHASE_ZOMBIQUARIUM_ACCEL = 0x3F,
	PHASE_ZOMBIQUARIUM_DRIFT = 0x40,
	PHASE_ZOMBIQUARIUM_BACK_AND_FORTH = 0x41,
	PHASE_ZOMBIQUARIUM_BITE = 0x42,
	PHASE_CATAPULT_LAUNCHING = 0x43,
	PHASE_CATAPULT_RELOADING = 0x44,
	PHASE_GARGANTUAR_THROWING = 0x45,
	PHASE_GARGANTUAR_SMASHING = 0x46,
	PHASE_IMP_GETTING_THROWN = 0x47,
	PHASE_IMP_LANDING = 0x48,
	PHASE_BALLOON_FLYING = 0x49,
	PHASE_BALLOON_POPPING = 0x4A,
	PHASE_BALLOON_WALKING = 0x4B,
	PHASE_LADDER_CARRYING = 0x4C,
	PHASE_LADDER_PLACING = 0x4D,
	PHASE_BOSS_ENTER = 0x4E,
	PHASE_BOSS_IDLE = 0x4F,
	PHASE_BOSS_SPAWNING = 0x50,
	PHASE_BOSS_STOMPING = 0x51,
	PHASE_BOSS_BUNGEES_ENTER = 0x52,
	PHASE_BOSS_BUNGEES_DROP = 0x53,
	PHASE_BOSS_BUNGEES_LEAVE = 0x54,
	PHASE_BOSS_DROP_RV = 0x55,
	PHASE_BOSS_HEAD_ENTER = 0x56,
	PHASE_BOSS_HEAD_IDLE_BEFORE_SPIT = 0x57,
	PHASE_BOSS_HEAD_IDLE_AFTER_SPIT = 0x58,
	PHASE_BOSS_HEAD_SPIT = 0x59,
	PHASE_BOSS_HEAD_LEAVE = 0x5A,
	PHASE_YETI_RUNNING = 0x5B,
	PHASE_SQUASH_PRE_LAUNCH = 0x5C,
	PHASE_SQUASH_RISING = 0x5D,
	PHASE_SQUASH_FALLING = 0x5E,
	PHASE_SQUASH_DONE_FALLING = 0x5F,
};
enum ZombieHeight
{
	HEIGHT_ZOMBIE_NORMAL = 0x0,
	HEIGHT_IN_TO_POOL = 0x1,
	HEIGHT_OUT_OF_POOL = 0x2,
	HEIGHT_DRAGGED_UNDER = 0x3,
	HEIGHT_UP_TO_HIGH_GROUND = 0x4,
	HEIGHT_DOWN_OFF_HIGH_GROUND = 0x5,
	HEIGHT_UP_LADDER = 0x6,
	HEIGHT_FALLING = 0x7,
	HEIGHT_IN_TO_CHIMNEY = 0x8,
	HEIGHT_GETTING_BUNGEE_DROPPED = 0x9,
	HEIGHT_ZOMBIQUARIUM = 0xA,
};
enum ShieldType
{
	SHIELDTYPE_NONE = 0x0,
	SHIELDTYPE_DOOR = 0x1,
	SHIELDTYPE_NEWSPAPER = 0x2,
	SHIELDTYPE_LADDER = 0x3,
};
enum PlantSubClass
{
	SUBCLASS_NORMAL = 0x0,
	SUBCLASS_SHOOTER = 0x1,
};
enum SeedType
{
	SEED_PEASHOOTER = 0x0,
	SEED_SUNFLOWER = 0x1,
	SEED_CHERRYBOMB = 0x2,
	SEED_WALLNUT = 0x3,
	SEED_POTATOMINE = 0x4,
	SEED_SNOWPEA = 0x5,
	SEED_CHOMPER = 0x6,
	SEED_REPEATER = 0x7,
	SEED_PUFFSHROOM = 0x8,
	SEED_SUNSHROOM = 0x9,
	SEED_FUMESHROOM = 0xA,
	SEED_GRAVEBUSTER = 0xB,
	SEED_HYPNOSHROOM = 0xC,
	SEED_SCAREDYSHROOM = 0xD,
	SEED_ICESHROOM = 0xE,
	SEED_DOOMSHROOM = 0xF,
	SEED_LILYPAD = 0x10,
	SEED_SQUASH = 0x11,
	SEED_THREEPEATER = 0x12,
	SEED_TANGLEKELP = 0x13,
	SEED_JALAPENO = 0x14,
	SEED_SPIKEWEED = 0x15,
	SEED_TORCHWOOD = 0x16,
	SEED_TALLNUT = 0x17,
	SEED_SEASHROOM = 0x18,
	SEED_PLANTERN = 0x19,
	SEED_CACTUS = 0x1A,
	SEED_BLOVER = 0x1B,
	SEED_SPLITPEA = 0x1C,
	SEED_STARFRUIT = 0x1D,
	SEED_PUMPKINSHELL = 0x1E,
	SEED_MAGNETSHROOM = 0x1F,
	SEED_CABBAGEPULT = 0x20,
	SEED_FLOWERPOT = 0x21,
	SEED_KERNELPULT = 0x22,
	SEED_INSTANT_COFFEE = 0x23,
	SEED_GARLIC = 0x24,
	SEED_UMBRELLA = 0x25,
	SEED_MARIGOLD = 0x26,
	SEED_MELONPULT = 0x27,
	SEED_GATLINGPEA = 0x28,
	SEED_TWINSUNFLOWER = 0x29,
	SEED_GLOOMSHROOM = 0x2A,
	SEED_CATTAIL = 0x2B,
	SEED_WINTERMELON = 0x2C,
	SEED_GOLD_MAGNET = 0x2D,
	SEED_SPIKEROCK = 0x2E,
	SEED_COBCANNON = 0x2F,
	SEED_IMITATER = 0x30,
	SEED_EXPLODE_O_NUT = 0x31,
	SEED_GIANT_WALLNUT = 0x32,
	SEED_SPROUT = 0x33,
	SEED_LEFTPEATER = 0x34,
	NUM_SEED_TYPES = 0x35,
	SEED_BEGHOULED_BUTTON_SHUFFLE = 0x36,
	SEED_BEGHOULED_BUTTON_CRATER = 0x37,
	SEED_SLOT_MACHINE_SUN = 0x38,
	SEED_SLOT_MACHINE_DIAMOND = 0x39,
	SEED_ZOMBIQUARIUM_SNORKLE = 0x3A,
	SEED_ZOMBIQUARIUM_TROPHY = 0x3B,
	SEED_ZOMBIE_NORMAL = 0x3C,
	SEED_ZOMBIE_TRAFFIC_CONE = 0x3D,
	SEED_ZOMBIE_POLEVAULTER = 0x3E,
	SEED_ZOMBIE_PAIL = 0x3F,
	SEED_ZOMBIE_LADDER = 0x40,
	SEED_ZOMBIE_DIGGER = 0x41,
	SEED_ZOMBIE_BUNGEE = 0x42,
	SEED_ZOMBIE_FOOTBALL = 0x43,
	SEED_ZOMBIE_BALLOON = 0x44,
	SEED_ZOMBIE_SCREEN_DOOR = 0x45,
	SEED_ZOMBONI = 0x46,
	SEED_ZOMBIE_POGO = 0x47,
	SEED_ZOMBIE_DANCER = 0x48,
	SEED_ZOMBIE_GARGANTUAR = 0x49,
	SEED_ZOMBIE_IMP = 0x4A,
	NUM_NONPLANT_SEEDS = 0x15,
	NUM_SEEDS_IN_CHOOSER = 0x31,
	SEED_NONE = 0xFFFFFFFF,
	BASE_NUM_SEED_TYPES = 0x35,
	SEED_UNOCCUPIED_START = 0x4B,
};
enum PlantState
{
	STATE_NOTREADY = 0x0,
	STATE_READY = 0x1,
	STATE_DOINGSPECIAL = 0x2,
	STATE_SQUASH_LOOK = 0x3,
	STATE_SQUASH_PRE_LAUNCH = 0x4,
	STATE_SQUASH_RISING = 0x5,
	STATE_SQUASH_FALLING = 0x6,
	STATE_SQUASH_DONE_FALLING = 0x7,
	STATE_GRAVEBUSTER_LANDING = 0x8,
	STATE_GRAVEBUSTER_EATING = 0x9,
	STATE_CHOMPER_BITING = 0xA,
	STATE_CHOMPER_BITING_GOT_ONE = 0xB,
	STATE_CHOMPER_BITING_MISSED = 0xC,
	STATE_CHOMPER_DIGESTING = 0xD,
	STATE_CHOMPER_SWALLOWING = 0xE,
	STATE_POTATO_RISING = 0xF,
	STATE_POTATO_ARMED = 0x10,
	STATE_POTATO_MASHED = 0x11,
	STATE_SPIKEWEED_ATTACKING = 0x12,
	STATE_SPIKEWEED_ATTACKING_2 = 0x13,
	STATE_SCAREDYSHROOM_LOWERING = 0x14,
	STATE_SCAREDYSHROOM_SCARED = 0x15,
	STATE_SCAREDYSHROOM_RAISING = 0x16,
	STATE_SUNSHROOM_SMALL = 0x17,
	STATE_SUNSHROOM_GROWING = 0x18,
	STATE_SUNSHROOM_BIG = 0x19,
	STATE_MAGNETSHROOM_SUCKING = 0x1A,
	STATE_MAGNETSHROOM_CHARGING = 0x1B,
	STATE_BOWLING_UP = 0x1C,
	STATE_BOWLING_DOWN = 0x1D,
	STATE_CACTUS_LOW = 0x1E,
	STATE_CACTUS_RISING = 0x1F,
	STATE_CACTUS_HIGH = 0x20,
	STATE_CACTUS_LOWERING = 0x21,
	STATE_TANGLEKELP_GRABBING = 0x22,
	STATE_COBCANNON_ARMING = 0x23,
	STATE_COBCANNON_LOADING = 0x24,
	STATE_COBCANNON_READY = 0x25,
	STATE_COBCANNON_FIRING = 0x26,
	STATE_KERNELPULT_BUTTER = 0x27,
	STATE_UMBRELLA_TRIGGERED = 0x28,
	STATE_UMBRELLA_REFLECTING = 0x29,
	STATE_IMITATER_MORPHING = 0x2A,
	STATE_ZEN_GARDEN_WATERED = 0x2B,
	STATE_ZEN_GARDEN_NEEDY = 0x2C,
	STATE_ZEN_GARDEN_HAPPY = 0x2D,
	STATE_MARIGOLD_ENDING = 0x2E,
	STATE_FLOWERPOT_INVULNERABLE = 0x2F,
	STATE_LILYPAD_INVULNERABLE = 0x30,
};
enum MagnetItemType
{
	MAGNET_ITEM_NONE = 0x0,
	MAGNET_ITEM_PAIL_1 = 0x1,
	MAGNET_ITEM_PAIL_2 = 0x2,
	MAGNET_ITEM_PAIL_3 = 0x3,
	MAGNET_ITEM_FOOTBALL_HELMET_1 = 0x4,
	MAGNET_ITEM_FOOTBALL_HELMET_2 = 0x5,
	MAGNET_ITEM_FOOTBALL_HELMET_3 = 0x6,
	MAGNET_ITEM_DOOR_1 = 0x7,
	MAGNET_ITEM_DOOR_2 = 0x8,
	MAGNET_ITEM_DOOR_3 = 0x9,
	MAGNET_ITEM_POGO_1 = 0xA,
	MAGNET_ITEM_POGO_2 = 0xB,
	MAGNET_ITEM_POGO_3 = 0xC,
	MAGNET_ITEM_JACK_IN_THE_BOX = 0xD,
	MAGNET_ITEM_LADDER_1 = 0xE,
	MAGNET_ITEM_LADDER_2 = 0xF,
	MAGNET_ITEM_LADDER_3 = 0x10,
	MAGNET_ITEM_LADDER_PLACED = 0x11,
	MAGNET_ITEM_SILVER_COIN = 0x12,
	MAGNET_ITEM_GOLD_COIN = 0x13,
	MAGNET_ITEM_DIAMOND = 0x14,
	MAGNET_ITEM_PICK_AXE = 0x15,
};
enum PlantOnBungeeState
{
	NOT_ON_BUNGEE = 0x0,
	GETTING_GRABBED_BY_BUNGEE = 0x1,
	RISING_WITH_BUNGEE = 0x2,
};
enum ProjectileMotion
{
	MOTION_STRAIGHT = 0x0,
	MOTION_LOBBED = 0x1,
	MOTION_THREEPEATER = 0x2,
	MOTION_BEE = 0x3,
	MOTION_BEE_BACKWARDS = 0x4,
	MOTION_PUFF = 0x5,
	MOTION_BACKWARDS = 0x6,
	MOTION_STAR = 0x7,
	MOTION_FLOAT_OVER = 0x8,
	MOTION_HOMING = 0x9,
	MOTION_LUNA = 0xA,
};
enum ProjectileType
{
	PROJECTILE_PEA = 0x0,
	PROJECTILE_SNOWPEA = 0x1,
	PROJECTILE_CABBAGE = 0x2,
	PROJECTILE_MELON = 0x3,
	PROJECTILE_PUFF = 0x4,
	PROJECTILE_WINTERMELON = 0x5,
	PROJECTILE_FIREBALL = 0x6,
	PROJECTILE_STAR = 0x7,
	PROJECTILE_SPIKE = 0x8,
	PROJECTILE_BASKETBALL = 0x9,
	PROJECTILE_KERNEL = 0xA,
	PROJECTILE_COBBIG = 0xB,
	PROJECTILE_BUTTER = 0xC,
	PROJECTILE_ZOMBIE_PEA = 0xD,
	NUM_PROJECTILES = 0xE,
	BASE_NUM_PROJECTILES = 0xE,
};
enum MessageStyle
{
	MESSAGE_STYLE_OFF = 0x0,
	MESSAGE_STYLE_TUTORIAL_LEVEL1 = 0x1,
	MESSAGE_STYLE_TUTORIAL_LEVEL1_STAY = 0x2,
	MESSAGE_STYLE_TUTORIAL_LEVEL2 = 0x3,
	MESSAGE_STYLE_TUTORIAL_LATER = 0x4,
	MESSAGE_STYLE_TUTORIAL_LATER_STAY = 0x5,
	MESSAGE_STYLE_HINT_LONG = 0x6,
	MESSAGE_STYLE_HINT_FAST = 0x7,
	MESSAGE_STYLE_HINT_STAY = 0x8,
	MESSAGE_STYLE_HINT_TALL_FAST = 0x9,
	MESSAGE_STYLE_HINT_TALL_10SECONDS = 0xA,
	MESSAGE_STYLE_HINT_TALL_LONG = 0xB,
	MESSAGE_STYLE_BIG_MIDDLE = 0xC,
	MESSAGE_STYLE_BIG_MIDDLE_FAST = 0xD,
	MESSAGE_STYLE_HOUSE_NAME = 0xE,
	MESSAGE_STYLE_HUGE_WAVE = 0xF,
	MESSAGE_STYLE_SLOT_MACHINE = 0x10,
	MESSAGE_STYLE_ZEN_GARDEN_LONG = 0x11,
};
enum GridSquareType
{
	GRIDSQUARE_NONE = 0x0,
	GRIDSQUARE_GRASS = 0x1,
	GRIDSQUARE_DIRT = 0x2,
	GRIDSQUARE_POOL = 0x3,
	GRIDSQUARE_HIGH_GROUND = 0x4,
};
enum PlantRowType
{
	PLANTROW_DIRT = 0x0,
	PLANTROW_NORMAL = 0x1,
	PLANTROW_POOL = 0x2,
	PLANTROW_HIGH_GROUND = 0x3,
};
enum BackgroundType
{
	BACKGROUND_1_DAY = 0x0,
	BACKGROUND_2_NIGHT = 0x1,
	BACKGROUND_3_POOL = 0x2,
	BACKGROUND_4_FOG = 0x3,
	BACKGROUND_5_ROOF = 0x4,
	BACKGROUND_6_BOSS = 0x5,
	BACKGROUND_MUSHROOM_GARDEN = 0x6,
	BACKGROUND_GREENHOUSE = 0x7,
	BACKGROUND_ZOMBIQUARIUM = 0x8,
	BACKGROUND_TREE_OF_WISDOM = 0x9,
};
enum TutorialState
{
	TUTORIAL_OFF = 0x0,
	TUTORIAL_LEVEL_1_PICK_UP_PEASHOOTER = 0x1,
	TUTORIAL_LEVEL_1_PLANT_PEASHOOTER = 0x2,
	TUTORIAL_LEVEL_1_REFRESH_PEASHOOTER = 0x3,
	TUTORIAL_LEVEL_1_COMPLETED = 0x4,
	TUTORIAL_LEVEL_2_PICK_UP_SUNFLOWER = 0x5,
	TUTORIAL_LEVEL_2_PLANT_SUNFLOWER = 0x6,
	TUTORIAL_LEVEL_2_REFRESH_SUNFLOWER = 0x7,
	TUTORIAL_LEVEL_2_COMPLETED = 0x8,
	TUTORIAL_MORESUN_PICK_UP_SUNFLOWER = 0x9,
	TUTORIAL_MORESUN_PLANT_SUNFLOWER = 0xA,
	TUTORIAL_MORESUN_REFRESH_SUNFLOWER = 0xB,
	TUTORIAL_MORESUN_COMPLETED = 0xC,
	TUTORIAL_SLOT_MACHINE_PULL = 0xD,
	TUTORIAL_SLOT_MACHINE_COMPLETED = 0xE,
	TUTORIAL_SHOVEL_PICKUP = 0xF,
	TUTORIAL_SHOVEL_DIG = 0x10,
	TUTORIAL_SHOVEL_KEEP_DIGGING = 0x11,
	TUTORIAL_SHOVEL_COMPLETED = 0x12,
	TUTORIAL_ZOMBIQUARIUM_BUY_SNORKEL = 0x13,
	TUTORIAL_ZOMBIQUARIUM_BOUGHT_SNORKEL = 0x14,
	TUTORIAL_ZOMBIQUARIUM_CLICK_TROPHY = 0x15,
	TUTORIAL_ZEN_GARDEN_PICKUP_WATER = 0x16,
	TUTORIAL_ZEN_GARDEN_WATER_PLANT = 0x17,
	TUTORIAL_ZEN_GARDEN_KEEP_WATERING = 0x18,
	TUTORIAL_ZEN_GARDEN_VISIT_STORE = 0x19,
	TUTORIAL_ZEN_GARDEN_FERTILIZE_PLANTS = 0x1A,
	TUTORIAL_ZEN_GARDEN_COMPLETED = 0x1B,
	TUTORIAL_WHACK_A_ZOMBIE_BEFORE_PICK_SEED = 0x1C,
	TUTORIAL_WHACK_A_ZOMBIE_PICK_SEED = 0x1D,
	TUTORIAL_WHACK_A_ZOMBIE_COMPLETED = 0x1E,
};
enum AdviceType
{
	ADVICE_NONE = 0xFFFFFFFF,
	ADVICE_CLICK_ON_SUN = 0x0,
	ADVICE_CLICKED_ON_SUN = 0x1,
	ADVICE_CLICKED_ON_COIN = 0x2,
	ADVICE_SEED_REFRESH = 0x3,
	ADVICE_CANT_AFFORD_PLANT = 0x4,
	ADVICE_PLANT_GRAVEBUSTERS_ON_GRAVES = 0x5,
	ADVICE_PLANT_LILYPAD_ON_WATER = 0x6,
	ADVICE_PLANT_TANGLEKELP_ON_WATER = 0x7,
	ADVICE_PLANT_SEASHROOM_ON_WATER = 0x8,
	ADVICE_PLANT_POTATOE_MINE_ON_LILY = 0x9,
	ADVICE_PLANT_WRONG_ART_TYPE = 0xA,
	ADVICE_PLANT_NEED_POT = 0xB,
	ADVICE_PLANT_NOT_ON_GRAVE = 0xC,
	ADVICE_PLANT_NOT_ON_CRATER = 0xD,
	ADVICE_CANT_PLANT_THERE = 0xE,
	ADVICE_PLANT_NOT_ON_WATER = 0xF,
	ADVICE_PLANTING_NEEDS_GROUND = 0x10,
	ADVICE_BEGHOULED_DRAG_TO_MATCH_3 = 0x11,
	ADVICE_BEGHOULED_MATCH_3 = 0x12,
	ADVICE_BEGHOULED_MATCH_4 = 0x13,
	ADVICE_BEGHOULED_SAVE_SUN = 0x14,
	ADVICE_BEGHOULED_USE_CRATER_1 = 0x15,
	ADVICE_BEGHOULED_USE_CRATER_2 = 0x16,
	ADVICE_PLANT_NOT_PASSED_LINE = 0x17,
	ADVICE_PLANT_ONLY_ON_REPEATERS = 0x18,
	ADVICE_PLANT_ONLY_ON_MELONPULT = 0x19,
	ADVICE_PLANT_ONLY_ON_SUNFLOWER = 0x1A,
	ADVICE_PLANT_ONLY_ON_SPIKEWEED = 0x1B,
	ADVICE_PLANT_ONLY_ON_KERNELPULT = 0x1C,
	ADVICE_PLANT_ONLY_ON_MAGNETSHROOM = 0x1D,
	ADVICE_PLANT_ONLY_ON_FUMESHROOM = 0x1E,
	ADVICE_PLANT_ONLY_ON_LILYPAD = 0x1F,
	ADVICE_PLANT_NEEDS_REPEATER = 0x20,
	ADVICE_PLANT_NEEDS_MELONPULT = 0x21,
	ADVICE_PLANT_NEEDS_SUNFLOWER = 0x22,
	ADVICE_PLANT_NEEDS_SPIKEWEED = 0x23,
	ADVICE_PLANT_NEEDS_KERNELPULT = 0x24,
	ADVICE_PLANT_NEEDS_MAGNETSHROOM = 0x25,
	ADVICE_PLANT_NEEDS_FUMESHROOM = 0x26,
	ADVICE_PLANT_NEEDS_LILYPAD = 0x27,
	ADVICE_SLOT_MACHINE_PULL = 0x28,
	ADVICE_HUGE_WAVE = 0x29,
	ADVICE_SHOVEL_REFRESH = 0x2A,
	ADVICE_PORTAL_RELOCATING = 0x2B,
	ADVICE_SLOT_MACHINE_COLLECT_SUN = 0x2C,
	ADVICE_DESTORY_POTS_TO_FINISIH_LEVEL = 0x2D,
	ADVICE_USE_SHOVEL_ON_POTS = 0x2E,
	ADVICE_ALMOST_THERE = 0x2F,
	ADVICE_ZOMBIQUARIUM_CLICK_TROPHY = 0x30,
	ADVICE_ZOMBIQUARIUM_COLLECT_SUN = 0x31,
	ADVICE_ZOMBIQUARIUM_CLICK_TO_FEED = 0x32,
	ADVICE_ZOMBIQUARIUM_BUY_SNORKEL = 0x33,
	ADVICE_I_ZOMBIE_PLANTS_NOT_REAL = 0x34,
	ADVICE_I_ZOMBIE_NOT_PASSED_LINE = 0x35,
	ADVICE_I_ZOMBIE_LEFT_OF_LINE = 0x36,
	ADVICE_SLOT_MACHINE_SPIN_AGAIN = 0x37,
	ADVICE_I_ZOMBIE_EAT_ALL_BRAINS = 0x38,
	ADVICE_PEASHOOTER_DIED = 0x39,
	ADVICE_STINKY_SLEEPING = 0x3A,
	ADVICE_BEGHOULED_NO_MOVES = 0x3B,
	ADVICE_PLANT_SUNFLOWER5 = 0x3C,
	ADVICE_PLANTING_NEED_SLEEPING = 0x3D,
	ADVICE_CLICK_TO_CONTINUE = 0x3E,
	ADVICE_SURVIVE_FLAGS = 0x3F,
	ADVICE_UNLOCKED_MODE = 0x40,
	NUM_ADVICE_TYPES = 0x41,
};
enum DebugTextMode
{
	DEBUG_TEXT_NONE = 0x0,
	DEBUG_TEXT_ZOMBIE_SPAWN = 0x1,
	DEBUG_TEXT_MUSIC = 0x2,
	DEBUG_TEXT_MEMORY = 0x3,
	DEBUG_TEXT_COLLISION = 0x4,
};
enum BoardResult
{
	BOARDRESULT_NONE = 0x0,
	BOARDRESULT_WON = 0x1,
	BOARDRESULT_LOST = 0x2,
	BOARDRESULT_RESTART = 0x3,
	BOARDRESULT_QUIT = 0x4,
	BOARDRESULT_QUIT_APP = 0x5,
	BOARDRESULT_CHEAT = 0x6,
};
enum ReanimLoopType
{
	REANIM_LOOP = 0x0,
	REANIM_LOOP_FULL_LAST_FRAME = 0x1,
	REANIM_PLAY_ONCE = 0x2,
	REANIM_PLAY_ONCE_AND_HOLD = 0x3,
	REANIM_PLAY_ONCE_FULL_LAST_FRAME = 0x4,
	REANIM_PLAY_ONCE_FULL_LAST_FRAME_AND_HOLD = 0x5,
};