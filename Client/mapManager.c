#include "mapManager.h"

static TexturePack get_texture_pack(int levelNumber){

    TexturePack level1 = {
        .paths = {
            {"Graphics/ny3.png"},
            {"Graphics/ny4.png"},
            {"Graphics/soffamatta3.png"},
            {"Graphics/soffamatta4.png"},
            {"Graphics/soffbord.png"},
            {"Graphics/byra.png"},
            {"Graphics/spis2.png"},
            {"Graphics/soffamatta1.png"},
            {"Graphics/soffamatta2.png"},
            {"Graphics/tv.png"},
            {"Graphics/kokbord2.png"},
            {"Graphics/kokbord.png"},
            {"Graphics/kyl.png"},
            {"Graphics/stolkok.png"},
            {"Graphics/mattagron.png"},
            {"Graphics/klinkers.png"},
            {"Graphics/mattahorn.png"},
            {"Graphics/mattasoffa.png"},
            {"Graphics/mattahorn2.png"},
            {"Graphics/disk.png"},
            {"Graphics/kok.png"}, //20
            {"Graphics/parkettny2.png"},
            {"Graphics/parkett2ny.png"},
            {"Graphics/vagghornV.png"},
            {"Graphics/vagghornH.png"},
            {"Graphics/vagghornVN.png"},
            {"Graphics/vagghornHN.png"},
            {"Graphics/parkett2ny2.png"},
            {"Graphics/gras.png"},
            {"Graphics/vaggN.png"}, //29 
            {"Graphics/stone.png"},
            {"Graphics/fonsterHH.png"},
            {"Graphics/fonster.png"},
            {"Graphics/fonsterV.png"},
            {"Graphics/klinkers1.png"},
            {"Graphics/bad1.png"},
            {"Graphics/bad2.png"},
            {"Graphics/toa.png"},
            {"Graphics/sang1.png"},
            {"Graphics/sang2.png"},
	{ "Graphics/handfat.png" }, //40
	{ "Graphics/badrumsmattaH.png" },
	{ "Graphics/badrumsmattaV.png" },
	{ "Graphics/toarulle.png" },
	{ "Graphics/handduk.png" }, //44
	{ "Graphics/handduk2.png" },
        },
        .numOfTextures = LEVEL_1_NUM_TEXTURES
    };
    
    TexturePack level2 = {
        .paths = {
            {"Graphics/sand.png"},
            {"Graphics/ben1.png"},
            {"Graphics/ben2.png"},
            {"Graphics/kaktus.png"},
            {"Graphics/kaktus2.png"},
            {"Graphics/kaktusvand.png"},
            {"Graphics/nystaket.png"},
            {"Graphics/orm.png"},
            {"Graphics/palm1.png"},
            {"Graphics/palm2.png"},
            {"Graphics/sten1.png"},
            {"Graphics/sten2.png"},
            {"Graphics/tunna.png"},
            {"Graphics/vatten1.png"},
            {"Graphics/vatten2.png"},
            {"Graphics/vatten4.png"},
            {"Graphics/vatten3.png"},
            {"Graphics/ormbunke.png"},
			{ "Graphics/brunnTundra.png" },
			{ "Graphics/skylt1.png" },
			{ "Graphics/skylt2.png" }, //20
        },
        .numOfTextures = LEVEL_2_NUM_TEXTURES
    };
	TexturePack level3 = {
		.paths = {
			{ "Graphics/hUpp.png" },
			{ "Graphics/hNer.png" },
			{"Graphics/pipeUpp.png"},
			{ "Graphics/pipeNer.png" },
			{ "Graphics/vUpp.png" },
			{ "Graphics/vNer.png" },
			{ "Graphics/kloakVatten.png" },
			{ "Graphics/pipeRakH.png" },
			{ "Graphics/pipeRakV.png" },
	{ "Graphics/gra.png" },
	{ "Graphics/hornHNER.png" },
	{ "Graphics/hornHNER2.png" },
	{ "Graphics/krokodil.png" },
	{ "Graphics/parkettny2.png" },
	{ "Graphics/horn1.png" },
	{ "Graphics/horn1_2.png" },//15
	{ "Graphics/grastrack.png" },
	{ "Graphics/slutNerV.png" },//17
	{ "Graphics/slutNerH.png" },//18
	{ "Graphics/slutUppV.png" },//19
	{ "Graphics/slutUppH.png" },//20
	{ "Graphics/horn2.png" },
	{ "Graphics/skrap.png" },
	{ "Graphics/rund.png" }, //23
	},
	.numOfTextures = LEVEL_3_NUM_TEXTURES
	};

	TexturePack level4 = {
		.paths = {
			{ "Graphics/labbGolv2.png" },
	{ "Graphics/datorNy.png" },
	{ "Graphics/datorNy2.png" },
	{ "Graphics/vaggLabbUPP.png" }, //3
	{ "Graphics/vaggLabbUPP.png" }, //4
	{ "Graphics/vaggLabbNER.png" }, //5
	{ "Graphics/vaggLabbNER.png" }, //6
	{ "Graphics/trasig.png" },
	{ "Graphics/trasig2.png" },
	{ "Graphics/GolvEjPassera2.png" },
	{ "Graphics/GolvEjPassera.png" },
	{ "Graphics/labbBankNy.png" }, //11
	{ "Graphics/varning2.png" },
	{ "Graphics/kloakVatten.png" }, //13
	{ "Graphics/vaggLabbHornHupp.png" },
	{ "Graphics/vaggLabbHner.png" },
	{ "Graphics/vaggLabbHornVup.png" },
	{ "Graphics/vaggLabbHornVner.png" },
	{ "Graphics/varning2.png" }, //18
	{ "Graphics/hUpp.png" },
	{ "Graphics/hNer.png" },
	{ "Graphics/pipeUpp.png" },
	{ "Graphics/pipeNer.png" },//22
	},
	.numOfTextures = LEVEL_4_NUM_TEXTURES
	};
    
    switch (levelNumber) {
        case LEVEL_1:
            return level1;
            break;
        case LEVEL_2:
            return level2;
            break;
		case LEVEL_3:
			return level3;
			break;
		case LEVEL_4:
			return level4;
			break;
		default:
            break;
    }
    
    return level1;
}

void mapManager_loadTextures(Level *level, SDL_Texture **mapTexture, SDL_Renderer *renderer)
{
    TexturePack pack = get_texture_pack(level->number);
    
    *mapTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, SCREEN_W, SCREEN_H);
    
    SDL_SetRenderTarget(renderer, *mapTexture);
    
    //Clear renderer
    SDL_RenderClear(renderer);
    
    SDL_Texture *tileTexture;
    char *texturePath;
    for(int row = 0; row < LEVEL_TILE_HEIGHT; row++){
        for(int column = 0; column < LEVEL_TILE_WIDTH; column++){
            texturePath = pack.paths[level->tile[row][column].type];
            
            tileTexture = TextureManager_loadTexture(texturePath, renderer);
            
            SDL_RenderCopy(renderer, tileTexture, &level->tile[row][column].srcRect, &level->tile[row][column].destRect);
            SDL_DestroyTexture(tileTexture);
        }
    }
    
    SDL_SetRenderTarget(renderer, NULL);
}
