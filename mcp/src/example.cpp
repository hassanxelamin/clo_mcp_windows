#include "stdafx.h"

#include "plugin.h"

#include "CLOAPIInterface.h"

#include <string>
#include <fstream>
#include <map>
#include <vector>

#if defined(__APPLE__)
#include <unistd.h>
#include <pwd.h>
#endif

// Test Codes in DoFunctions (0: Deactivate, 1: Activate)
///////////////////////////////////////
#define TEST_ALL_FUNCTIONS									0
//////////////////////////////////////

#define USE_RENDERINGIMAGE_SAMPLE									0
#define USE_EXPORT_TECHPACK_SAMPLE									0
#define USE_EXPORT_OBJ_SAMPLE										0
#define USE_EXPORT_ZPRJ_SAMPLE										0
#define USE_FABRIC_SAMPLE											0
#define USE_PROGRESSBAR_SAMPLE										0
#define USE_EXPORT_SIMULATION_SAMPLE								0
#define USE_GET_INFORMATIONS_SAMPLE									0
#define USE_GET_CUSTOM_VIEW_SAMPLE									0
#define USE_COLORWAY_NAME_SAMPLE									0
#define USE_REST_API_TEST											0
#define USE_UNICODE_FUNCTION_TEST									0
#define USE_ADD_COLORCHIP_TEST										0
#define USE_NEW_PROJECT_TEST										0
#define USE_FABRIC_FILE_METADATA_TEST								0
#define USE_GET_CLO_FILE_PATH_TEST									0
#define USE_EXPORT_TURNTABLE_IMAGES									0
#define USE_EXPORT_GLTF_TEST										0
#define USE_EXPORT_TURNTABLE_VIDEO									0
#define USE_READ_WRITE_METADATA_FILE								0
#define USE_SET_WINDOWS_TITLE_3D_TEST								0
#define USE_COPY_COLORWAY_TEST										0
#define USE_GARMENT_INFO_TEST										0
#define USE_GARMENT_INFO_CONFIG_TEST								0
#define USE_EXPORT_TECHPACK_TO_STREAM_TEST							0
#define USE_EXPORT_THUMBNAIL3D_TEST									0
#define USE_EXPORT_SNAPSHOT3D_TEST									0
#define USE_EXPORT_SINGLE_COLORWAY_RENDERING_IMAGE_TEST				0
#define USE_GET_RENDER_IMAGE_RELATED_PATHS_TEST						0
#define USE_GET_FILE_NAME_ON_RENDERING_PROPERTY_TEST				0
#define USE_GET_COLORWAY_RELATED_INFORMATION_TEST					0
#define USE_GET_SIZE_RELATED_INFORMATION_TEST						0
#define USE_GET_FABRIC_RELATED_INFORMATION_TEST						0
#define USE_CHANGE_FABRIC_WITH_JSON_TEST							0
#define USE_ASSIGN_FABRIC_TO_PATTERN_TEST							0
#define USE_EXPORT_ANIMATION_VIDEO									0
#define USE_IMPORT_ZPRJ_SAMPLE										0
#define USE_IMPORT_FILE_SAMPLE										0
#define USE_EXPORT_ZPAC_TEST										0
#define USE_AVATAR_RELATED_API_TEST									0
#define USE_PATTERN_RELATED_API_TEST								0
#define USE_VERSION_CHECK_API_TEST									0
#define USE_EXPORT_GLB_TEST											0
#define USE_SAVE_FABRIC_CUSTOME_THUMBNAIL_TEST						0
#define USE_IMPORT_OBJ_SAMPLE										0
#define USE_IMPORT_VMP_SAMPLE										0
#define USE_IMPORT_CPT_SAMPLE										0
#define USE_IMPORT_VLP_SAMPLE										0
#define USE_IMPORT_VRP_SAMPLE										0
#define USE_FABRICINFORMATION_TEST									0
#define USE_PRIMARY_FABRIC_API_TEST									0
#define USE_GET_COLORLIST_FOR_COLORWAY_TEST							0
#define USE_EXPORT_POM_TEST											0
#define USE_SHOW_HIDE_AVATAR_TEST									0
#define USE_SCHEMATIC_RENDER_TEST									0
#define USE_GET_PATTERN_PIECE_AREA_TEST								0
#define USE_GET_LINE_LENGTH_TEST									0
#define USE_GET_PATTERN_INPUT_INFORMATION_TEST						0
#define USE_GET_PATTERN_BOUNDING_BOX_TEST							0
#define USE_GET_PATTERNS_BOUNDING_BOX_TEST							0
#define USE_GET_PATTERN_PARTICLE_DISTANCE_TEST						0
#define USE_GET_PATTERN_MESH_COUNT_TEST								0
#define USE_GET_PATTERN_SHRINKAGE_PERCENTAGE_TEST					0
#define USE_IMPORT_DXF_FILE_SAMPLE									0
#define USE_UPDATE_COLOWAYS											0
#define USE_EXPORT_THUMBNAIL3D_FOR_COLORWAYS						0
#define USE_SET_PATTERN_PARTICLE_DISTANCE_TEST						0
#define USE_SET_PATTERNS_PARTICLE_DISTANCE_TEST						0
#define USE_SET_MESH_TYPE_TEST										0
#define USE_SET_WIDTH_PATTERN_SHRINKAGE_PERCENTAGE_TEST				0
#define USE_SET_HEIGHT_PATTERN_SHRINKAGE_PERCENTAGE_TEST			0
#define USE_GET_ARRANGEMENTLIST_TEST								0
#define USE_GET_PATTERN_ARRANGEMENT_TEST							0
#define USE_GET_PATTERNS_ARRANGEMENT_TEST							0
#define USE_SET_ARRANGEMENT_SHAPE_STYLE_TEST						0
#define USE_SET_ARRANGEMENT_POSITION_TEST							0
#define USE_SET_ARRANGEMENT_ORIENTATION_TEST						0
#define USE_SET_ARRANGEMENT_TEST									0
#define USE_EXPORT_POSE_TEST										0
#define USE_EXPORT_FBX_TEST											0
#define USE_DELETE_COLORWAY_ITEM_TEST								0
#define USE_COPY_PATTERN_PIECE_POS_TEST								0
#define USE_COPY_PATTERN_PIECE_MOVE_TEST							0
#define USE_DELETE_PATTERN_PIECE_TEST								0
#define USE_DELETE_LINE_PIECE_TEST									0
#define USE_DELETE_POINT_PIECE_TEST									0
#define USE_FLIP_PATTERN_PIECE_TEST									0
#define USE_LAYER_CLONE_PATTERN_PIECE_POS_TEST						0
#define USE_LAYER_CLONE_PATTERN_PIECE_MOVE_TEST						0
#define USE_OFFSET_AS_INTERNAL_LINE_TEST							0
#define USE_UNFOLD_PATTERN_PIECE_TEST								0
#define USE_CONVER_TO_BASE_LINE_TEST								0
#define USE_CONVER_TO_INTERNAL_LINE_TEST							0
#define USE_DISTRIBUE_INTERNAL_LINES_BETWEEN_SEGMENTS_TEST			0
#define USE_IMPORT_GRAPHICSTYLE_TEST								0
#define USE_REPLACE_GRAPHICSTYLE_TEST								0
#define USE_GET_PATTERN_PIECE_POS_TEST								0
#define USE_SET_PATTERN_PIECE_POS_TEST								0
#define USE_SET_PATTERN_PIECE_MOVE_TEST								0
#define USE_ELASTIC_TEST											0
#define USE_ELASTIC_STRENGTH_TEST									0
#define USE_ELASTIC_STRENGTH_RATIO_TEST								0
#define USE_ELASTIC_SEGMENT_LENGTH_TEST								0
#define USE_ELASTIC_TOTAL_LENGTH_TEST								0
#define USE_SHIRRING_TEST											0
#define USE_SHIRRING_INTERVAL_TEST									0
#define USE_SHIRRING_HEIGHT_TEST									0
#define USE_SHIRRING_EXTEND_TEST									0
#define USE_SEAMTAPING_TEST											0
#define USE_SEAMTAPING_WIDTH_TEST									0
#define USE_PATTERN_PIECE_INFO_TEST									0
#define USE_PATTERN_PIECE_FABRIC_STYLE_INFO_TEST					0
#define USE_PATTERN_PIECE_SOLIDIFY_INFO_TEST						0
#define USE_GET_FABRIC_STYLE_NAME_LIST_TEST							0
#define USE_SET_PATTERN_LAYER_TEST									0
#define USE_GET_PATTERN_LAYER_TEST									0
#define USE_SET_PATTERN_STRENGTHEN_TEST								0
#define USE_SET_PATTERN_LOCK_TEST									0
#define USE_SET_PATTERN_HIDE_3D_TEST								0
#define USE_SET_PATTERN_FREEZE_TEST									0
#define USE_ADD_SEGMENT_TOPSTITCH_TEST								0
#define USE_GET_TOPSTITCH_STYLE_LIST_TEST							0
#define USE_GET_PATTERN_ASSIGNED_TOPSTITCH_COUNT_TEST				0
#define USE_GET_PATTERN_ASSIGNED_TOPSTITCH_STYLE_TEST				0
#define USE_GET_PATTERN_ASSIGNED_TOPSTITCH_TEST						0
#define USE_GET_PATTERN_ASSIGNED_TOPSTITCH_STYLE_INDEX_TEST			0
#define USE_SET_PATTERN_ASSIGNED_TOPSTITCH_STYLE_TEST				0
#define USE_IS_PATTERN_ASSIGNED_TOPSTITCH_EXTEND_START_TEST			0
#define USE_SET_PATTERN_ASSIGNED_TOPSTITCH_EXTEND_START_TEST		0
#define USE_IS_PATTERN_ASSIGNED_TOPSTITCH_EXTEND_END_TEST			0
#define USE_SET_PATTERN_ASSIGNED_TOPSTITCH_EXTEND_END_TEST			0
#define USE_IS_PATTERN_ASSIGNED_TOPSTITCH_CURVED_TEST				0
#define USE_SET_PATTERN_ASSIGNED_TOPSTITCH_CURVED_TEST				0
#define USE_GET_PATTERN_ASSIGNED_TOPSTITCH_CURVED_LENGTH_TEST		0
#define USE_SET_PATTERN_ASSIGNED_TOPSTITCH_CURVED_LENGTH_TEST		0
#define USE_IS_PATTERN_ASSIGNED_TOPSTITCH_CURVED_RIGHT_ANGLED_TEST	0
#define USE_SET_PATTERN_ASSIGNED_TOPSTITCH_CURVED_RIGHT_ANGLED_TEST 0
#define USE_GET_PATTERN_ASSIGNED_TOPSTITCH_ZOFFSET_TEST				0
#define USE_SET_PATTERN_ASSIGNED_TOPSTITCH_ZOFFSET_TEST				0
#define USE_IMPORT_TOPSTITCH_STYLE_TEST								0
#define USE_CREATE_PATTERN_WITH_POINTS								0
#define USE_IMPORT_AVAC_SAMPLE										0
#define USE_SET_AVATAR_TEXTURE_SAMPLE								0
#define USE_IMPORT_FILE_BY_OBJ_TYPE_SAMPLE							0
#define USE_IMPORT_FBX_SAMPLE										0
#define USE_IMPORT_GLTF_SAMPLE										0
#define USE_SET_ANIMATION_RECORDING_TEST							0
#define USE_SET_CURRENT_ANIMATION_FRAME_TEST						0
#define USE_GET_CURRENT_ANIMATION_FRAME_TEST						0
#define USE_SET_START_ANIMATION_FRAME_TEST							0
#define USE_GET_START_ANIMATION_FRAME_TEST							0
#define USE_SET_END_ANIMATION_FRAME_TEST							0
#define USE_GET_END_ANIMATION_FRAME_TEST							0
#define USE_IMPORT_SMP_SAMPLE										0
#define USE_IMPORT_SUBSTANCE_FILE_AS_FACETYPE_SAMPLE				0
#define USE_IMPORT_AS_GRAPHIC										0
#define USE_IMPORT_TRIM												0
#define USE_EXPORT_AVT_SAMPLE										0
#define USE_SET_TEXTURE_MAPPING										0
#define USE_SET_SUBSTANCE_PRESET									0
#define USE_SET_SUBSTANCE_RESOLUTION								0
#define USE_ANNOTATION_TEST											0
#define USE_GET_LINKED_PATTERN_INDEX_TEST							0
#define USE_GET_SET_STRESS_MAP_RENDERED_STATUS						0
#define USE_GET_SET_STRAIN_MAP_RENDERED_STATUS						0
#define USE_REFRESH_PLUGINS											0
#define USE_SET_CAM_VIEW_POINT_TEST									0
#define USE_SET_USE_SAME_MATERIAL_AS_FRONT							0
#define USE_SET_USE_SAME_COLOR_AS_FRONT								0
#define USE_SET_SCHEMATIC_SILHOUETTE_LINE_WIDTH						0
#define USE_SET_SCHEMATIC_SEAM_LINE_WIDTH							0
#define USE_SET_SCHEMATIC_INTERNAL_LINE_WIDTH						0
#define USE_SET_SCHEMATIC_TOPSTITCH_LINE_SCALE_PERCENT				0
#define USE_SET_SCHEMATIC_BRIGHTNESS								0
#define USE_SET_SHOW_SCHEMATIC_SILHOUETTE_LINE						0
#define USE_SET_SHOW_SCHEMATIC_SEAM_LINE							0
#define USE_SET_SHOW_SCHEMATIC_INTERNAL_LINE						0
#define USE_SET_SHOW_SCHEMATIC_TOPSTITCH_LINE						0
#define USE_SET_SCHEMATIC_CLOTH_RENDER_TYPE							0
#define USE_SET_STYLE_LINE_COLOR									0
#define USE_SET_SCHEMATIC_CLOTH_COLOR								0
#define USE_CREATE_MODULAR_CATEGORY_API_SAMPLE						0
#define USE_DELETE_MODULAR_CATEGORY_API_SAMPLE						0
#define USE_GET_TOPSTITCH_STYLE_MODEL_TYPE							0
#define USE_SET_TOPSTITCH_STYLE_MODEL_TYPE							0
#define USE_CREATE_ZFAB_FROM_TEXTURE								0
#define USE_COMBINE_ZFAB											0
#define USE_BAKE_UV_TEXTURE											0
#define USE_UV_PACKING												0
#define USE_GET_ROUGHNESS_CONFIG_OF_MATERIAL_IN_FABRIC				0
#define USE_SET_ROUGHNESS_CONFIG_OF_MATERIAL_IN_FABRIC				0
#define USE_EXPORT_TRIM_SAMPLE										0
#define USE_SET_TRIM_WEIGHT											0
#define USE_EXPORT_OBJECTBROWSER_MATERIAL_LIST						0
#define USE_GET_ALL_PIN_LIST										0
#define USE_REMOVE_SELECTED_PIN										0
#define USE_EXPORT_STD_VIEW_IMAGES									0
#define USE_EXPORT_STD_VIEW_IMAGES_FOR_ALL_COLORWAYS				0
#define USE_EXPORT_CUSTOM_VIEW_IMAGES								0
#define USE_EXPORT_CUSTOM_VIEW_IMAGES_FOR_ALL_COLORWAYS				0
#define USE_EXPORT_MULTI_VIEW_IMAGES								0
#define USE_EXPORT_MULTI_VIEW_IMAGES_FOR_ALL_COLORWAYS				0
#define USE_CHANGING_GRADING_SIZE									0
#define USE_REFRESH_3D_WINDOW										0
#define USE_COVERT_ZBLC_TO_ZMOD										0
#define USE_SET_COLORWAY_COLOR_ITEM									0
#define USE_GET_COLORWAY_COLOR_ITEM_RGB								0
#define USE_GET_COLORWAY_COLOR_ITEM_PLM_ID							0
#define USE_GET_COLORWAY_COLOR_ITEM_NAME							0
#define USE_REMOVE_PLUGIN_FROM_LIST									0
#define USE_ADD_PLUGIN_FROM_FILE									0
#define USE_PLUGIN_FROM_LIST										0
#define USE_TERMINATE_PLUGIN_FROM_LIST								0
#define USE_EXPORT_POM_3D_LENGTH_TEST								0
#define USE_DISPLACEMENT_MAP_API_TEST                               0
#define USE_ADD_SEAMLINE_STITCH_TEST								0
#define USE_GET_SEAMLINE_PAIR_GROUP_COUNT_TEST						0
#define USE_GET_SEAMLINE_PAIR_GOUP_NAME_TEST						0
#define USE_GET_SEAMLINE_PAIR_GROUP_INDEX_FROM_NAME_TEST			0
#define USE_GET_ALL_STITCH_PROPERTY_TEST							0
#define USE_ADD_SEAMLINE_PAIR_GROUP_TEST							0
#define USE_GET_GRADING_PAIRED_AVATAR								0
#define USE_EXPORT_PATTERN_JSON										0
#define USE_IMPORT_PATTERN_JSON										0
#define USE_GET_REFLECTION_ROUGHNESS								0
#define USE_SET_REFLECTION_ROUGHNESS								0
#define USE_GET_REFLECTION_INTENSITY								0
#define USE_SET_REFLECTION_INTENSITY								0
#define USE_GET_METALNESS											0
#define USE_SET_METALNESS											0
#define USE_GET_NORMAL_MAP_INTENSITY								0
#define USE_SET_NORMAL_MAP_INTENSITY								0
#define USE_SET_3D_GARMENT_RENDERING_STYLE_SAMPLE					0
#define USE_GET_MATERIAL_TYPE										0
#define USE_SET_MATERIAL_TYPE										0
#define USE_GET_OPACITY_INTENSITY									0
#define USE_SET_OPACITY_INTENSITY									0
#define USE_LOAD_LIBRARY_COLOR_SWATCH_LIST_TEST						0
#define USE_ADD_LIBRARY_COLOR_SWATCH_LIST_TEST						0
#define USE_SET_COLOR_SWATCH_LIST_ITEM_NAME_TEST					0
#define USE_DELETE_COLOR_SWATCH_LIST_ITEM_TEST						0
#define USE_SET_COLOR_SWATCH_LIBRARY_TAB_NAME_TEST					0
#define USE_DELETE_COLOR_SWATCH_LIBRARY_TAB_BY_NAME_TEST				0
#define USE_GET_TOTAL_GRAPHIC_ITEM_QUANTITY							0
#define USE_GET_GRAPHIC_STYLE_COUNT									0
#define USE_GET_GRAPHIC_STYLE_NAME									0
#define USE_GET_GRAPHIC_STYLE_DIMENSIONS							0
#define USE_SET_GRAPHIC_STYLE_NAME									0
#define USE_SET_GRAPHIC_STYLE_DIMENSIONS							0
#define USE_SET_GRAPHIC_STYLE_WIDTH									0
#define USE_SET_GRAPHIC_STYLE_HEIGHT								0
#define USE_GET_BASETEXTUREMAP_IMAGE_FILE_PATH_TEST					0
#define USE_GET_NORMALMAP_IMAGE_FILE_PATH_TEST						0
#define USE_GET_DISPLACEMENT_IMAGE_FILE_PATH_TEST					0
#define USE_GET_OPACITYMAP_IMAGE_FILE_PATH_TEST						0
#define USE_GET_ROUGHNESSMAP_IMAGE_FILE_PATH_TEST					0
#define USE_GET_METALNESSMAP_IMAGE_FILE_PATH_TEST					0
#define USE_SET_BASETEXTUREMAP_IMAGE_FILE_PATH_TEST					0
#define USE_SET_NORMALMAP_IMAGE_TEST								0
#define USE_SET_DISPLACEMENTMAP_IMAGE_TEST							0
#define USE_SET_OPACITYMAP_IMAGE_TEST								0
#define USE_SET_ROUGHNESSMAP_IMAGE_TEST								0
#define USE_SET_METALNESSMAP_IMAGE_TEST								0
#define USE_SET_EXPORT_BOM_TEST										0
#define USE_SET_EXPORT_BOM_TEST										0
#define USE_REPLACE_FABRIC										    0
#define USE_EXPORT_USD_TEST											0
#define USE_AUTO_HANG_TEST											0

using namespace std;
using namespace CLOAPI;

static std::string base64_encode(const std::string &in) {

	std::string out;

	int val = 0, valb = -6;
	for (unsigned char c : in) {
		val = (val << 8) + c;
		valb += 8;
		while (valb >= 0) {
			out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val >> valb) & 0x3F]);
			valb -= 6;
		}
	}
	if (valb > -6) out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val << 8) >> (valb + 8)) & 0x3F]);
	while (out.size() % 4) out.push_back('=');
	return out;
}

string getHomePath()
{
	string homePath = "C:/";

#if defined(__APPLE__)
	const char *homeDir = getenv("HOME");

	if (homeDir == nullptr)
	{
		struct passwd* pwd = getpwuid(getuid());
		if (pwd)
		   homeDir = pwd->pw_dir;
	}

	if (homeDir)
    {
		homePath = homeDir;
        homePath = homePath + "/";
    }
	else
    {
		homePath = "/usr/local/";
    }
#endif

	return homePath;
}

void ExportZprjSample()
{
	if (!EXPORT_API || !UTILITY_API)
		return;

	string exportPath = UTILITY_API->GetCLOTemporaryFolderPath() + "test.zprj";
	EXPORT_API->ExportZPrj(exportPath, true);

	string msg = "Export Zprj Complete: " + exportPath;
	UTILITY_API->DisplayMessageBox(msg);
}

void ExportTechPack_Sample()
{
	if (!EXPORT_API || !UTILITY_API)
		return;

	fprintf(stdout, "Start Export Tech Pack !! ========================== \n");

	string exportPath = UTILITY_API->GetCLOTemporaryFolderPath() + "test.json";
	string baseFolder = getHomePath() + "Zpac/";

	exportPath = baseFolder + "test1/test.json";
	Marvelous::ExportTechpackOption option(Marvelous::CLO_DUMMY);

	// set flags for 3D Baseline for capturing
	option.m_ShowBaseLineFor3DCapturePerColorway[0] = false;
	option.m_ShowBaseLineFor3DCapturePerColorway[1] = true;
	option.m_ShowBaseLineFor3DCapturePerColorway[2] = false;
	//option.m_ShowBaseLineFor3DCapturePerColorway[3] = true; - as-is

	EXPORT_API->ExportTechPack(exportPath, option);
	//
	exportPath = baseFolder + "test2/test.json";
	option.m_bUseAverageColor = true;
	EXPORT_API->ExportTechPack(exportPath, option);

	//
	exportPath = baseFolder + "test3/test.json";
	option.m_bUseAverageColor = false;

	option.m_bCapturePatternLayoutThumbnailWithFabricMark = true;
	option.m_bCapturePatternLayoutThumbnailWithTrimMark = true;
	EXPORT_API->ExportTechPack(exportPath, option);

	//
	exportPath = baseFolder + "test4/test.json";
	option.m_bCaptureItemThumbnail = true;
	option.m_bCapturePatternLayoutThumbnailWithTrimMark = true;
	EXPORT_API->ExportTechPack(exportPath, option);

	//
	exportPath = baseFolder + "test5/test.json";
	option.m_bCaptureSceneThumbnailWithoutAvatar = true;
	option.m_bCaptureSceneThumbnailWithMark = true;
	option.m_bCaptureSceneThumbnailWithAvatar = true;
	EXPORT_API->ExportTechPack(exportPath, option);

	//
	exportPath = baseFolder + "test6/test.json";
	option.m_bSaveZpac = true;
	option.m_bSaveZprj = true;
	EXPORT_API->ExportTechPack(exportPath, option);

	fprintf(stdout, "========================== END of the TEST ========================== \n");
}

void ExportTechPackW_Sample()
{
	if (!EXPORT_API || !UTILITY_API)
		return;

	fprintf(stdout, "Start Export Tech Pack !! ========================== \n");

	string baseFolder = getHomePath() + "Zpac/";

	wstring exportPath = UTILITY_API->GetCLOTemporaryFolderPathW() + L"test.json";
	wstring baseFolderW(baseFolder.begin(), baseFolder.end());

	exportPath = baseFolderW + L"테스트1/테스트.json";
	Marvelous::ExportTechpackOption option(Marvelous::CLO_DUMMY);

	EXPORT_API->ExportTechPackW(exportPath, option);

	//
	exportPath = baseFolderW + L"테스트2/테스트.json";
	option.m_bUseAverageColor = true;
	EXPORT_API->ExportTechPackW(exportPath, option);

	//
	exportPath = baseFolderW + L"테스트3/테스트.json";
	option.m_bUseAverageColor = false;

	option.m_bCapturePatternLayoutThumbnailWithFabricMark = true;
	option.m_bCapturePatternLayoutThumbnailWithTrimMark = true;
	EXPORT_API->ExportTechPackW(exportPath, option);

	//
	exportPath = baseFolderW + L"테스트4/테스트.json";
	option.m_bCaptureItemThumbnail = true;
	option.m_bCapturePatternLayoutThumbnailWithTrimMark = true;
	EXPORT_API->ExportTechPackW(exportPath, option);

	//
	exportPath = baseFolderW + L"테스트5/테스트.json";
	option.m_bCaptureSceneThumbnailWithoutAvatar = true;
	option.m_bCaptureSceneThumbnailWithMark = true;
	option.m_bCaptureSceneThumbnailWithAvatar = true;
	EXPORT_API->ExportTechPackW(exportPath, option);

	//
	exportPath = baseFolderW + L"테스트6/테스트.json";
	option.m_bSaveZpac = true;
	option.m_bSaveZprj = true;
	EXPORT_API->ExportTechPackW(exportPath, option);

	wstring techpack_stream = EXPORT_API->ExportTechPackToStreamW(exportPath);
	UTILITY_API->DisplayMessageBoxW(techpack_stream);
	UTILITY_API->DisplayMessageBoxW(exportPath);

	fprintf(stdout, "========================== END of the TEST ========================== \n");
}

void HttpGetTest()
{
	if (!REST_API)
		return;

	string id = ""; // set the clo id
	string pw = ""; // set the clo pw
	pw = UTILITY_API->stringToMD5(pw); // change the clo pw with md5 hashed in lower cases

	string basicAuthorizationString = "Basic " + base64_encode(id + ":" + pw);

	vector<pair<string, string>> headerNameAndValueList;
	headerNameAndValueList.push_back(make_pair("Authorization", basicAuthorizationString));
	headerNameAndValueList.push_back(make_pair("X-User-Product", "24"));

	string url = "https://api.clo3d.com/auth/versioncheck?version=2.5.9999.299999&product=24&ostype=2207&processbit=3001";
	string response = REST_API->CallRESTGet(url, headerNameAndValueList, "HTTP Get");
	fprintf(stdout, "\n\n");
	fprintf(stdout, response.c_str());
	fprintf(stdout, "\n\n");

	UTILITY_API->DisplayMessageBox(response);

	unsigned char* buffer = nullptr;
	unsigned int size = 0;

	REST_API->GetByteArrayFromStream(response, buffer, size);

	string str((const char*)buffer);
	UTILITY_API->DisplayMessageBox(str);

	UTILITY_API->DisplayMessageBox(to_string(size));

	delete buffer;
	buffer = nullptr;
	size = 0;
}

void HttpPostTest()
{
	if (!REST_API)
		return;

	string id = ""; // set the clo id
	string pw = ""; // set the clo pw with md5 hashed in lower cases
	string basicAuthorizationString = "Basic " + base64_encode(id + ":" + pw);

	vector<pair<string, string>> headerNameAndValueList;
	headerNameAndValueList.push_back(make_pair("Host", "api.clo3d.com"));
	headerNameAndValueList.push_back(make_pair("Authorization", basicAuthorizationString));
	headerNameAndValueList.push_back(make_pair("Cache-Control", "no-cache"));
	headerNameAndValueList.push_back(make_pair("Content-Type", "application/x-www-form-urlencoded"));
	headerNameAndValueList.push_back(make_pair("X-User-Product", "24"));

	string parameter = "userid=kylelee&password=2ce46905cb1530c3c1e2149634854ce4&product=24&version=2.5.9999.299999";

	string response = REST_API->CallRESTPost("https://api.clo3d.com/auth/login", &parameter, headerNameAndValueList, "HTTP Post test");
	fprintf(stdout, "\n\n");
	fprintf(stdout, response.c_str());
	fprintf(stdout, "\n\n");
}

void CreatePattern_Test()
{
	// init rectangle
	vector<tuple<float, float, int>> createPatternPoints = {
		make_tuple(0.0f, -300.0f, 0)
		, make_tuple(0.0f, -200.0f, 0)
		, make_tuple(100.0f, -200.0f, 0)
		, make_tuple(100.0f, -300.0f, 0)
	};
	PATTERN_API->CreatePatternWithPoints(createPatternPoints);

	// free polygon
	createPatternPoints.clear();
	createPatternPoints.push_back(make_tuple(0.0f, 0.0f, 0));
	createPatternPoints.push_back(make_tuple(0.0f, 100.0f, 3));
	createPatternPoints.push_back(make_tuple(100.0f, 100.0f, 0));
	createPatternPoints.push_back(make_tuple(200.0f, 100.0f, 3));
	createPatternPoints.push_back(make_tuple(150.0f, 50.0f, 3));
	createPatternPoints.push_back(make_tuple(200.0f, 50.0f, 0));
	createPatternPoints.push_back(make_tuple(300.0f, 50.0f, 3));
	createPatternPoints.push_back(make_tuple(250.0f, 100.0f, 3));
	createPatternPoints.push_back(make_tuple(300.0f, 100.0f, 0));
	createPatternPoints.push_back(make_tuple(350.0f, 100.0f, 3));
	createPatternPoints.push_back(make_tuple(300.0f, 50.0f, 0));
	createPatternPoints.push_back(make_tuple(150.0f, 0.0f, 2));
	PATTERN_API->CreatePatternWithPoints(createPatternPoints);
	////////////////////////////////////////////////

	// half circle
	createPatternPoints.clear();
	createPatternPoints.push_back(make_tuple(0.0f, 200.0f, 0));
	createPatternPoints.push_back(make_tuple(0.0f, 300.0f, 3));
	createPatternPoints.push_back(make_tuple(100.0f, 300.0f, 0));
	createPatternPoints.push_back(make_tuple(200.0f, 300.0f, 3));
	createPatternPoints.push_back(make_tuple(200.0f, 200.0f, 0));
	PATTERN_API->CreatePatternWithPoints(createPatternPoints);
	// innershape in half circle
	createPatternPoints.clear();
	createPatternPoints.push_back(make_tuple(0.0f, 200.0f, 0));
	createPatternPoints.push_back(make_tuple(0.0f, 250.0f, 3));
	createPatternPoints.push_back(make_tuple(50.0f, 250.0f, 0));
	createPatternPoints.push_back(make_tuple(100.0f, 250.0f, 3));
	createPatternPoints.push_back(make_tuple(100.0f, 200.0f, 0));
	PATTERN_API->CreateInternalShapeWithPoints(2, createPatternPoints, false);
	// baseshape in half circle
	createPatternPoints.clear();
	createPatternPoints.push_back(make_tuple(0.0f, 200.0f, 0));
	createPatternPoints.push_back(make_tuple(0.0f, 225.0f, 3));
	createPatternPoints.push_back(make_tuple(25.0f, 225.0f, 0));
	createPatternPoints.push_back(make_tuple(50.0f, 225.0f, 3));
	createPatternPoints.push_back(make_tuple(50.0f, 200.0f, 0));
	PATTERN_API->CreateBaseShapeWithPoints(2, createPatternPoints, false);
}

void HttpPost2Test()
{
	if (!REST_API)
		return;

	string id = ""; // set the clo id
	string pw = ""; // set the clo pw with md5 hashed in lower cases
	string basicAuthorizationString = "Basic " + base64_encode(id + ":" + pw);

	vector<pair<string, string>> headerNameAndValueList;
	headerNameAndValueList.push_back(make_pair("Host", "api.clo3d.com"));
	headerNameAndValueList.push_back(make_pair("Authorization", basicAuthorizationString));
	headerNameAndValueList.push_back(make_pair("Cache-Control", "no-cache"));
	headerNameAndValueList.push_back(make_pair("Content-Type", "application/x-www-form-urlencoded"));
	headerNameAndValueList.push_back(make_pair("X-User-Product", "24"));

	string parameter = "userid=kylelee&password=2ce46905cb1530c3c1e2149634854ce4&product=24&version=2.5.9999.299999";

	unsigned char *postField = new unsigned char[parameter.length() + 1];
	std::strcpy((char*)postField, parameter.c_str());
	unsigned int size = (unsigned int)(parameter.length()) + 1;

	string response = REST_API->CallRESTPost2("https://api.clo3d.com/auth/login", postField, size, headerNameAndValueList, "HTTP Post2 test");
	fprintf(stdout, "\n\n");
	fprintf(stdout, response.c_str());
	fprintf(stdout, "\n\n");
}

void UploadToCLOSET(const string& filePath)
{
	if (!REST_API)
		return;

	vector<pair<string, string>> headerNameAndValueList;

	string response = REST_API->CallRESTPostWithMultipartFormData("https://www.clo-set.com/api/item", filePath, headerNameAndValueList, "Upload...");
	fprintf(stdout, "\n\n");
	fprintf(stdout, response.c_str());
	fprintf(stdout, "\n\n");
	UTILITY_API->DisplayMessageBox(response);
}

void ExportThumbnail3D_Sample()
{
	if (!EXPORT_API)
		return;

	EXPORT_API->ExportThumbnail3D();
}

void ExportSnapshot3D_Sample()
{
	if (!EXPORT_API)
		return;

	EXPORT_API->ExportSnapshot3D();
}

void ExportGarmentInformation_Sample()
{
	if (!EXPORT_API)
		return;

	string baseFolder = getHomePath() + "Zpac/";
	string filePath = baseFolder + "info.json";

	EXPORT_API->ExportGarmentInformation(filePath);
}

void ImportGarmentInformation_Sample()
{
	if (!IMPORT_API)
		return;

	string baseFolder = getHomePath() + "Zpac/";
	string filePath = baseFolder + "info.json";

	IMPORT_API->ImportGarmentInformation(filePath);
}

void ExportGarmentInformationConfigData_Sample()
{
	if (!EXPORT_API)
		return;

	string baseFolder = getHomePath() + "Zpac/";
	string filePath = baseFolder + "configData.json";

	EXPORT_API->ExportGarmentInformationConfigData(filePath);
}

void ImportGarmentInformationConfigData_Sample()
{
	if (!IMPORT_API)
		return;

	string baseFolder = getHomePath() + "Zpac/";
	string filePath = baseFolder + "configData.json";

	IMPORT_API->ImportGarmentInformationConfigData(filePath);
}

void ExportRenderingImage_Sample()
{
	if (!EXPORT_API)
		return;

	vector< vector<std::string>> savedFilePathList = EXPORT_API->ExportRenderingImage(true);
}

void ExportOBJ_Sample()
{
	if (!EXPORT_API)
		return;

	Marvelous::ImportExportOption options;
	options.bExportAvatar = false;
	options.bExportGarment = true;
	options.bSaveInZip = true;
	// the other options are given as default. please refer to ImportExportOption class in ExportAPI.h

	vector<string> exportedFilePathList;
	if (options.bSaveInZip)
	{
		string baseFolder = getHomePath() + "Zpac/";
		exportedFilePathList = EXPORT_API->ExportOBJ(baseFolder + "test.obj", options); // returns only a file path for a zipped file including OBJ, MTL, and image files.

		// exportedFilePathList[0] -> a zip file

	}
	else
	{
		exportedFilePathList = EXPORT_API->ExportOBJ(options); // returns OBJ and MTL files. In addition, MTL files for colorways will be created as well.

		// exportedFilePathList[0] -> OBJ
		// exportedFilePathList[1] -> MTL for the current colorway
		// exportedFilePathList[2] -> MTL for the first colorway
		// exportedFilePathList[3] -> MTL for the second colorway
		// ...
		// exportedFilePathList[exportedFilePathList.size()-1]-> MTL for the last colorway
	}

	for (auto& path : exportedFilePathList)
	{
		if (UTILITY_API)
			UTILITY_API->DisplayMessageBox(path);
	}

}

void ExportDXF_Sample()
{
	Marvelous::ExportDxfOption exportOption;
	exportOption.m_RotateAngle = 90;
	exportOption.m_fScale = 2.0f;

	string baseFolder = getHomePath() + "export_dxf/";

	if (EXPORT_API)
		EXPORT_API->ExportDXF(baseFolder + "test.dxf", exportOption);
}

void ExportFabric_Sample()
{
	if (FABRIC_API == nullptr)
		return;

	int index = 0; // default fabric, the 1st fabric on the object browser in CLO S/W

	string baseFolder = getHomePath() + "fabric/";
	string jFabFilePath = baseFolder + "test.jfab";
	string zFabFilePath = baseFolder + "test.zfab";

	FABRIC_API->ExportZFab(jFabFilePath, index);
	FABRIC_API->ExportZFab(zFabFilePath, index);

}

void ImportFabric_Sample()
{
	if (FABRIC_API == nullptr)
		return;

	string baseFolder = getHomePath() + "fabric/";
	string jFabFilePath = baseFolder + "test.jfab";
	string zFabFilePath = baseFolder + "test.zfab";

	unsigned int addedFabricIndexFromJson = FABRIC_API->AddFabric(jFabFilePath);
	unsigned int addedFabricIndexFromZfab = FABRIC_API->AddFabric(zFabFilePath);

	string xTexFilePath = baseFolder + "test.xTex"; // use any xTex file(with textures folder) you have

	FABRIC_API->ImportXtexFile(addedFabricIndexFromJson, xTexFilePath);
	FABRIC_API->ImportXtexFile(addedFabricIndexFromZfab, xTexFilePath);
	FABRIC_API->ApplyXtexFile(addedFabricIndexFromJson, xTexFilePath);
	FABRIC_API->ApplyXtexFile(addedFabricIndexFromZfab, xTexFilePath);
}

void DeleteFabric_Sample()
{
	if (FABRIC_API == nullptr)
		return;

	const string fabricName = "CLO_FABRIC_2019_1";

	int fabricIndex = FABRIC_API->GetFabricIndex(fabricName);

	if (fabricIndex > 0) // 0 is default fabric
		FABRIC_API->DeleteFabric(fabricIndex);
}

string GetSampleMetaData()
{
	string sampleMetaData = "{\n"; // start element	
	sampleMetaData += "\"itemID\": \"CLO_GR_2019_09_30_001\""; // itemId
	sampleMetaData += ",\n";
	sampleMetaData += "\"serviceDivision\": \"CLO Service Division\""; // service division
	sampleMetaData += ",\n";
	sampleMetaData += "\"brand\": \"CLO Luxury\""; // brand
	sampleMetaData += ",\n";
	sampleMetaData += "\"productType\": \"Blazer\""; // product type
	sampleMetaData += "\n}\n"; // end element

	return sampleMetaData;
}

void GarmentMetaData_Sample()
{
	if (UTILITY_API == nullptr)
		return;

	// sample meta data
	string sampleMetaData = GetSampleMetaData();

	// set sample meta data
	UTILITY_API->SetMetaDataForCurrentGarment(sampleMetaData);

	// get sample meta data
	string curMetaData = UTILITY_API->GetMetaDataForCurrentGarment();
	UTILITY_API->DisplayMessageBox(curMetaData);

	// change sample meta data
	string metaDataKey1 = "serviceDivision";
	string newValue1 = "MD Service Division";

	string metaDataKey2 = "brand";
	string newValue2 = "MD CG Studio";

	UTILITY_API->ChangeMetaDataValueForCurrentGarment(metaDataKey1, newValue1);
	UTILITY_API->ChangeMetaDataValueForCurrentGarment(metaDataKey2, newValue2);
	UTILITY_API->DisplayMessageBox(UTILITY_API->GetMetaDataForCurrentGarment());
}

void FabricMetaData_Sample()
{
	if (UTILITY_API == nullptr || FABRIC_API == nullptr)
		return;

	// sample meta data
	string sampleMetaData = GetSampleMetaData();

	FABRIC_API->SetAPIMetaData(1, sampleMetaData);
	FABRIC_API->ChangeMetaDataValueForFabric(1, "testKey", "testValue");

	string apiMetaData = FABRIC_API->GetAPIMetaData(1);
	UTILITY_API->DisplayMessageBox(apiMetaData);
}

void ProgressBar_Sample()
{
	if (UTILITY_API == nullptr)
		return;

	UTILITY_API->CreateProgressBar();

	for (int i = 0; i < 10; ++i)
	{
		UTILITY_API->SetProgress("Progress... ", (int)(float(i) / 10.0f * 100));
#ifdef __APPLE__ 
		sleep(1);
#else
		Sleep(200);
#endif
	}

	UTILITY_API->DeleteProgressBar(false);
}

void GetInformations_Sample()
{
	string fabricInfo = FABRIC_API->GetFabricInfo(0);
	UTILITY_API->DisplayMessageBox(fabricInfo);

	string patternInfo = PATTERN_API->GetPatternInformation(0);
	UTILITY_API->DisplayMessageBox(patternInfo);
}

void GetCustomView_Sample()
{
	string customViewInfo = UTILITY_API->GetCustomViewInformation();
	UTILITY_API->DisplayMessageBox(customViewInfo);
}

void ColorwayName_Sample()
{
	// colorway count
	unsigned int colorwayCount = UTILITY_API->GetColorwayCount();
	string msg = "Colorway Count: " + to_string(colorwayCount);
	UTILITY_API->DisplayMessageBox(msg);

	// current colorway index
	unsigned int currentColorwayIndex = UTILITY_API->GetCurrentColorwayIndex();
	msg = "Current Colorway Index: " + to_string(currentColorwayIndex);
	UTILITY_API->DisplayMessageBox(msg);

	// colorway name
	wstring wName = UTILITY_API->GetColorwayNameW(UTILITY_API->GetCurrentColorwayIndex());
	wName = L"Current Colorway Name: " + wName;
	UTILITY_API->DisplayMessageBoxW(wName);

	wName = L"WAPITEST_ColorwayName";
	UTILITY_API->SetColorwayNameW(currentColorwayIndex, wName);
	UTILITY_API->UpdateColorways();

	// set colorway index test
	UTILITY_API->SetCurrentColorwayIndex(1);
	currentColorwayIndex = UTILITY_API->GetCurrentColorwayIndex();
	msg = "Current Colorway Index: " + to_string(currentColorwayIndex);
	UTILITY_API->DisplayMessageBox(msg);

	wName = UTILITY_API->GetColorwayNameW(UTILITY_API->GetCurrentColorwayIndex());
	wName = L"Current Colorway Name: " + wName;
	UTILITY_API->DisplayMessageBoxW(wName);
}

void UnicodeFunctionsTest()
{
	wofstream fi;
#ifdef __APPLE__ 
	string baseFolder = getHomePath() + "Zpac/";
	string test_log_file = baseFolder + "log.txt";
	fi.imbue(locale("ko_KR.UTF-8"));
	fi.open((const char*)test_log_file.c_str());
#else
	wstring test_log_file = L"C:/Zpac/log.txt";
	fi.imbue(locale("ko_KR.UTF-8"));
	fi.open(test_log_file);
#endif

	/// Fabric API test
	fi << L"############# Start Fabric API Test ########### " << endl;

	// ExportZFabW
	fi << L"wstring ExportZFabW" << endl;

#ifdef __APPLE__ 
	string zfabFilePath = baseFolder + "test.zfab";
	wstring zfabFilePathW(zfabFilePath.begin(), zfabFilePath.end());
#else
	wstring zfabFilePathW = L"C:\\Zpac\\test.zfab";
#endif

	wstring retValue = FABRIC_API->ExportZFabW(zfabFilePathW, 0);

	fi << L"Exported ZFab file " << endl;
	fi << L"--> Value : " << retValue << endl;

	fi << endl;

	// ExportFabricW
	fi << L"wstring ExportFabricW" << endl;

#ifdef __APPLE__ 
	string jfabFilePath = baseFolder + "test.jfab";
	wstring jfabFilePathW(jfabFilePath.begin(), jfabFilePath.end());
#else
	wstring jfabFilePathW = L"C:\\Zpac\\test.jfab";
#endif

	retValue = FABRIC_API->ExportFabricW(jfabFilePathW, 0);

	fi << L"Exported Fabric file " << endl;
	fi << L"--> Value : " << retValue << endl;

	fi << endl;

	// AddFabricW
	fi << L"unsigned int AddFabricW" << endl;

	unsigned int fabricIndex = FABRIC_API->AddFabricW(zfabFilePathW);

	fi << L"Added Fabric Index for " << zfabFilePathW << endl;
	fi << L"--> Value : " << to_wstring(fabricIndex) << endl;

	fi << endl;

	// GetFirstFabricTextureNameW
	fi << L"wstring GetFirstFabricTextureNameW" << endl;
	wstring firstTextureName = FABRIC_API->GetFirstFabricTextureNameW();

	fi << L"First Fabric Texture Name" << endl;
	fi << L"--> Value : " << firstTextureName << endl;

	fi << endl;

	wstring fabricName = FABRIC_API->GetFabricNameW(0);
	UTILITY_API->DisplayMessageBoxW(fabricName);

	// GetFabricNameW
	fi << L"Fabric Name for Index 0 " << endl;
	fi << L"--> Value : " << fabricName << endl;

	fi << endl;

	// GetFabricIndexW
	fabricIndex = FABRIC_API->GetFabricIndexW(fabricName);
	fi << L"Fabric index for " << fabricName << endl;
	fi << L"--> Value : " << to_wstring(fabricIndex) << endl;

	/// Pattern API test
	fi << L"############# Start Pattern API Test ########### " << endl;
	unsigned int patternIndex = 0;
	wstring patternInfo = PATTERN_API->GetPatternInformationW(patternIndex);
	fi << L"Pattern Information for Pattern Index: " << to_wstring(patternIndex) << endl;
	fi << patternInfo << endl << endl;
	UTILITY_API->DisplayMessageBoxW(patternInfo);

	fi << L"############# Finalize Pattern API Test ########### " << endl;

	/// Export API test
	fi << L"############# Start Export API Test ########### " << endl;
	wstring garmentInfo = EXPORT_API->ExportGarmentInformationToStreamW();
	fi << L"Garment Information: " << endl;
	fi << garmentInfo << endl << endl;
	UTILITY_API->DisplayMessageBoxW(garmentInfo);

	wstring garmenetConfigData = EXPORT_API->ExportGarmentInformationConfigDataToStreamW();
	fi << L"Garment Information Config Data : " << endl;
	fi << garmenetConfigData << endl << endl;
	UTILITY_API->DisplayMessageBoxW(garmenetConfigData);

	wstring techpackOutputPath;
	wstring techpackInfo = EXPORT_API->ExportTechPackToStreamW(techpackOutputPath);
	fi << L"Techpack Information: " << endl;
	fi << techpackInfo << endl << endl;
	UTILITY_API->DisplayMessageBoxW(techpackInfo);

	fi << L"############# Finalize Export API Test ########### " << endl;

	/// Utility API test	
	fi << L"############# Start Utility API Test ########### " << endl;
	wstring tempFolder = UTILITY_API->GetCLOTemporaryFolderPathW();
	fi << L"CLO Temporary folder created : " << endl;
	fi << tempFolder << endl;

	wstring projectName = UTILITY_API->GetProjectNameW();
	fi << L"Project Name : " << endl;
	fi << projectName << endl;

	wstring projectFilePath = UTILITY_API->GetProjectFilePathW();
	fi << L"Project File Path : " << endl;
	fi << projectFilePath << endl;

	wstring customViewInfo = UTILITY_API->GetCustomViewInformationW();
	fi << L"Custom View Information: " << endl;
	fi << customViewInfo << endl << endl;
	UTILITY_API->DisplayMessageBoxW(customViewInfo);

	fi << L"############# Finalize Utility API Test ########### " << endl;

	fi.close();

#ifdef __APPLE__
	UTILITY_API->DisplayMessageBox(test_log_file);
#else
	UTILITY_API->DisplayMessageBoxW(test_log_file);
#endif
}

void GetCustomViewWithZcmrTest()
{
	vector<wstring> cameraFiles;

	string baseFolder = getHomePath() + "Zpac/";
	wstring baseFolderW(baseFolder.begin(), baseFolder.end());

	cameraFiles.push_back(baseFolderW + L"Custom_View_1.zcmr");
	cameraFiles.push_back(baseFolderW + L"Custom_View_2.zcmr");
	cameraFiles.push_back(baseFolderW + L"Custom_View_3.zcmr");
	cameraFiles.push_back(baseFolderW + L"Custom_View_4.zcmr");
	cameraFiles.push_back(baseFolderW + L"Custom_View_5.zcmr");
	cameraFiles.push_back(baseFolderW + L"Custom_View_6.zcmr");
	cameraFiles.push_back(baseFolderW + L"Custom_View_7.zcmr");
	cameraFiles.push_back(baseFolderW + L"Custom_View_8.zcmr");
	cameraFiles.push_back(baseFolderW + L"Custom_View_9.zcmr");
	cameraFiles.push_back(baseFolderW + L"Custom_View_10.zcmr");

	for (size_t i = 0; i < cameraFiles.size(); ++i)
		IMPORT_API->ImportFileW(cameraFiles[i]);

	string imageFilePath = baseFolder + "output_image";
	vector<string> outputPath = EXPORT_API->ExportCustomViewSnapshot(imageFilePath, 512, 512, "sample");
}

void AddColorChip_Sample()
{
	if (UTILITY_API == nullptr)
		return;

	wstring swatchName = L"CLO_API_CUSTOM_SWATCH";
	map<wstring, wstring> plmIdToNameList;
	map<wstring, Marvelous::CloApiRgb> plmIdToColorList;
	map<wstring, wstring> plmIdToApiMetaDataList;

	Marvelous::CloApiRgb color;
	color.R = 255;

	// 1. red
	plmIdToNameList[L"CLO_API_RED"] = L"CLO_API_RED";
	plmIdToColorList[L"CLO_API_RED"] = color;

	wstring apiMetaData = L"{\r\n\"KEY1_FOR_RED\":\"CLO_API_RED_VALUE1\", \r\n\"KEY2_FOR_RED\":\"CLO_API_RED_VALUE2\"}";
	plmIdToApiMetaDataList[L"CLO_API_RED"] = apiMetaData;

	// 2. green
	color.R = 0;
	color.G = 255;

	plmIdToNameList[L"CLO_API_GREEN"] = L"CLO_API_GREEN";
	plmIdToColorList[L"CLO_API_GREEN"] = color;

	apiMetaData = L"{\r\n\"KEY1_FOR_GREEN\":\"CLO_API_GREEN_VALUE1\", \r\n\"KEY2_FOR_GREEN\":\"CLO_API_GREEN_VALUE2\"}";
	plmIdToApiMetaDataList[L"CLO_API_GREEN"] = apiMetaData;

	// 3. blue
	color.R = 0;
	color.G = 0;
	color.B = 255;

	plmIdToNameList[L"CLO_API_BLUE"] = L"CLO_API_BLUE";
	plmIdToColorList[L"CLO_API_BLUE"] = color;

	apiMetaData = L""; // empty meta data test
	plmIdToApiMetaDataList[L"CLO_API_BLUE"] = apiMetaData;

	// 2. white
	color.R = 255;
	color.G = 255;
	color.B = 255;

	plmIdToNameList[L"CLO_API_WHITE"] = L"CLO_API_WHITE";
	plmIdToColorList[L"CLO_API_WHITE"] = color;

	apiMetaData = L""; // empty meta data test
	plmIdToApiMetaDataList[L"CLO_API_WHITE"] = apiMetaData;

	// add colorchip to color pallete
	UTILITY_API->AddColorSwatchW(plmIdToNameList, plmIdToColorList, plmIdToApiMetaDataList, swatchName);
}

void LoadLibraryColorSwatchList_Sample()
{
	std::vector<std::string> library = { 
		"C:/palette/color_swatch_sample_1.cco",
		"C:/palette/color_swatch_sample_2.cco",
		"C:/palette/color_swatch_sample_3.cco",
	};

	UTILITY_API->LoadLibraryColorSwatchList(library, "TabName");
}

void AddLibraryColorSwatchList_Sample()
{
	std::vector<std::string> library = { 
		"C:/palette/color_swatch_sample_1.cco",
		"C:/palette/color_swatch_sample_2.cco",
		"C:/palette/color_swatch_sample_3.cco",
	};

	std::string tabName = "test";

	UTILITY_API->AddLibraryColorSwatchList(library, tabName);
}

void SetColorSwatchListItemName_Sample()
{
	std::string tabName = "test";
	int index = 0;
	std::string itemName = "new name";

	UTILITY_API->SetColorSwatchListItemName(tabName, 0, itemName);
}

void DeleteColorSwatchListItem_Sample()
{
	std::string tabName = "test";
	int index = 0;

	UTILITY_API->DeleteColorSwatchListItem(tabName, index);
}

void SetColorSwatchLibraryTabName_Sample()
{
	std::string tabName = "test";
	std::String newTabName = "new tab name";

	UTILITY_API->SetColorSwatchLibraryTabName(tabName, newTabName);
}

void DeleteColorSwatchLibraryTabByName_Sample()
{
	std::string tabName = "test";
	bool bCaseInsensitive = true;

	UTILITY_API->DeleteColorSwatchLibraryTabByName(tabName, bCaseInsensitive);
}

void NewProject_Sample()
{
	if (UTILITY_API == nullptr)
		return;

	UTILITY_API->NewProject();
}

void FabricFileMetaData_Sample()
{
	if (FABRIC_API == nullptr || UTILITY_API == nullptr)
		return;

	string baseFolder = getHomePath() + "fabric/";
	string testZFab = baseFolder + "test.zfab";
	wstring testZFabW(testZFab.begin(), testZFab.end());

	string metaData = FABRIC_API->GetAPIMetaDataFromFile(testZFab);
	UTILITY_API->DisplayMessageBox(metaData);

	wstring metaDataW = FABRIC_API->GetAPIMetaDataFromFileW(testZFabW);
	UTILITY_API->DisplayMessageBoxW(metaDataW);
}

void GetCLOFilePath_Sample()
{
	if (UTILITY_API == nullptr)
		return;

	string executableFolderPath = UTILITY_API->GetCLOExecutableFolderPath(true); // path delimiter '/'
	UTILITY_API->DisplayMessageBox(executableFolderPath);

	wstring executableFolderPathW = UTILITY_API->GetCLOExecutableFolderPathW(false); // path delimiter '\\'
	UTILITY_API->DisplayMessageBoxW(executableFolderPathW);

	string assetFolderPathForCurrentVersion = UTILITY_API->GetCLOAssetFolderPath(false); // path delimiter '\\'
	UTILITY_API->DisplayMessageBox(assetFolderPathForCurrentVersion);

	wstring assetFolderPathForCurrentVersionW = UTILITY_API->GetCLOAssetFolderPathW(true); // path delimiter '/'
	UTILITY_API->DisplayMessageBoxW(assetFolderPathForCurrentVersionW);
}

void ExportTurntableImages_Sample()
{
	if (EXPORT_API == nullptr)
		return;

	// save current scene turntable images
	string savePath = getHomePath() + "Zpac/" + "test.png";
	EXPORT_API->ExportTurntableImages(savePath, 12);

	UTILITY_API->DisplayMessageBox(savePath);

	// save colorway turntable images
	unsigned int colorwayIndex = 0;
	vector<string> savedPathList = EXPORT_API->ExportTurntableImagesByColorwayIndex(12, colorwayIndex);

	if (savedPathList.empty() == false)
		UTILITY_API->DisplayMessageBox(savedPathList.front());
}

void ExportTurntableVideos_Sample()
{
	if (EXPORT_API == nullptr)
		return;

	string baseFolder = getHomePath() + "export_videos/";
	EXPORT_API->ExportTurntableVideo(baseFolder + "turntable_video_output.avi");
}

void ExportAnimationVideos_Sample()
{
	if (EXPORT_API == nullptr)
		return;

	string baseFolder = getHomePath() + "export_videos/";
	EXPORT_API->ExportAnimationVideo(baseFolder + "animation_video_output.avi");
}

void ReadWriteMetaDataFile_Sample()
{
	if (UTILITY_API == nullptr)
		return;

	string baseFolder = getHomePath() + "test_metadata/";
	string filePath = baseFolder + "test_metadata_file.zprj";
	
	string sampleMetaData = "{\n"; // start element	
	sampleMetaData += "\"metaData1\": \"Merong\""; // itemId
	sampleMetaData += "\n}\n"; // end element

	string preVal = UTILITY_API->GetAPIMetaData(filePath);
	UTILITY_API->DisplayMessageBox(preVal);

	UTILITY_API->SetAPIMetaData(filePath, sampleMetaData);

	string val = UTILITY_API->GetAPIMetaData(filePath);
	UTILITY_API->DisplayMessageBox(val);
}

void ExportGLTF_Sample()
{
	if (!EXPORT_API)
		return;

	Marvelous::ImportExportOption options;
	options.bExportAvatar = false;
	options.bExportGarment = true;
	options.bSaveInZip = true;
	options.scale = 0.001f; // gltf scale

	// the other options are given as default. please refer to ImportExportOption class in ExportAPI.h

	vector<string> exportedFilePathList;
	string baseFolder = getHomePath() + "export_gltf/";
	exportedFilePathList = EXPORT_API->ExportGLTF(baseFolder + "test.gltf", options, false); // returns only a file path for a zipped file including GLTF and BIN files.

	for (auto& path : exportedFilePathList)
	{
		if (UTILITY_API)
			UTILITY_API->DisplayMessageBox(path);
	}
}

void ExportAlembic_Sample()
{
	if (!EXPORT_API)
		return;

	Marvelous::ImportExportOption options;
	options.bExportAvatar = false;
	options.bExportGarment = true;
	options.scale = 0.001f;

	// the other options are given as default. please refer to ImportExportOption class in ExportAPI.h

	vector<string> exportedFilePathList;
	string baseFolder = getHomePath() + "export_abc/";
	exportedFilePathList = EXPORT_API->ExportAlembic(baseFolder + "test.abc", options);

	for (auto& path : exportedFilePathList)
	{
		if (UTILITY_API)
			UTILITY_API->DisplayMessageBox(path);
	}
}

void ExportUSD_Sample()
{
	if (!EXPORT_API)
		return;

	// the options are given as default. please refer to ImportExportOption class and  in ExportAPI.h
	Marvelous::ImportExportOption options;
	Marvelous::ExportUSDOption usdOptions;
	
	vector<string> exportedFilePathList;
	string baseFolder = getHomePath() + "export_usd/";
	exportedFilePathList = EXPORT_API->ExportUSD(baseFolder + "test.usd", options, usdOptions);

	for (auto& path : exportedFilePathList)
	{
		if (UTILITY_API)
			UTILITY_API->DisplayMessageBox(path);
	}
}

void SetWindowsTitle3D_Sample()
{
	wstring _title = L"CLO API Sample Windows 3D";
	if (UTILITY_API)
		UTILITY_API->Set3DWindowTitleW(_title);
}

void CopyColorway_Sample()
{
	if (UTILITY_API == nullptr)
		return;

	unsigned newColorwayIndex = UTILITY_API->CopyColorway(2, 0);
	if (newColorwayIndex == 0)
		return;

	string newColorwayName = "Colorway By CLO API";
	UTILITY_API->SetColorwayName(newColorwayIndex, newColorwayName);

	UTILITY_API->UpdateColorways();
}

void ExportTechPackToStream_Sample()
{
	if (!EXPORT_API || !UTILITY_API)
		return;

	fprintf(stdout, "Start Export Tech Pack to Stream !! ========================== \n");

	string exportPath = UTILITY_API->GetCLOTemporaryFolderPath() + "test.json";
	string outputPath = EXPORT_API->ExportTechPackToStream(exportPath);

	fprintf(stdout, "========================== END of the TEST ========================== \n");
}

void ExportSingleColorwayRenderingImage_Sample()
{
	if (!EXPORT_API)
		return;

	unsigned int defaultIndex = 0;
	vector<string> outputPath = EXPORT_API->ExportSingleColorwayRenderingImage(defaultIndex);
}

void GetTotalRenderImagePaths_Sample()
{
	if (!EXPORT_API || !UTILITY_API)
		return;

	vector<string> outputPath = EXPORT_API->GetTotalRenderImagePaths();

	string resultPaths = "Total Render Image Paths :\n";
	for (const auto& path : outputPath)
	{
		resultPaths.append(path + "\n");
	}
	UTILITY_API->DisplayMessageBox(resultPaths);
}

void GetCurrentRenderImagePaths_Sample()
{
	if (!EXPORT_API || !UTILITY_API)
		return;

	vector<string> outputPath = EXPORT_API->GetCurrentRenderImagePaths();

	string resultPaths = "Current Render Image Paths :\n";
	for (const auto& path : outputPath)
	{
		resultPaths.append(path + "\n");
	}
	UTILITY_API->DisplayMessageBox(resultPaths);
}

void GetFileNameOnRenderingProperty_Sample()
{
	if (!EXPORT_API || !UTILITY_API)
		return;

	string resultMsg = EXPORT_API->GetFileNameOnRenderingProperty();
	UTILITY_API->DisplayMessageBox(resultMsg);
}

void GetColorwayRelatedInformation_Sample()
{
	if (!EXPORT_API || !UTILITY_API)
		return;

	string msg = "";
	unsigned int count = EXPORT_API->GetColorwayCount();
	msg.append("ColorWay count : " + to_string(count) + "\n");

	unsigned int currentIndex = EXPORT_API->GetCurrentColorwayIndex();
	msg.append("Current colorWay index : " + to_string(currentIndex) + "\n");
	
	
	vector<string> outputName = EXPORT_API->GetColorwayNameList();
	msg.append("Colorway name list : ");
	for (const auto& name : outputName)
	{
		msg.append(name + " ");
	}
	UTILITY_API->DisplayMessageBox(msg);
}

void GetSizeRelatedInformation_Sample()
{
	if (!EXPORT_API || !UTILITY_API)
		return;

	string msg = "";
	unsigned int count = PATTERN_API->GetGradingSizeTotalCount();
	msg.append("Size count : " + to_string(count) + "\n");

	unsigned int currentIndex = PATTERN_API->GetCurrentGradingSizeIndex();
	msg.append("Current size index : " + to_string(currentIndex) + "\n");


	vector<string> outputName = PATTERN_API->GetGradingSizeNameList();
	msg.append("Size name list : ");
	for (const auto& name : outputName)
	{
		msg.append(name + " ");
	}
	UTILITY_API->DisplayMessageBox(msg);
}

void GetFabricRelatedInformation_Sample()
{
	if (!FABRIC_API || !UTILITY_API)
		return;

	string msg = "";
	unsigned int count = FABRIC_API->GetFabricCount();
	msg.append("Fabric count : " + to_string(count) + "\n");

	unsigned int currentIndex = FABRIC_API->GetCurrentFabricIndex();
	msg.append("Current fabric index : " + to_string(currentIndex) + "\n");

	string fabricTextureName = FABRIC_API->GetFirstFabricTextureName();
	msg.append("First fabric texture name : " + fabricTextureName + "\n");

	int defaultPatternIndex = 0; // Get fabric index for pattern #0
	int patternFabricIndex = FABRIC_API->GetFabricIndexForPattern(defaultPatternIndex);
	msg.append("Fabric index for pattern : " + to_string(patternFabricIndex) + "\n");

	string defaultFabricName = "FABRIC 1";
	int fabricIndex = FABRIC_API->GetFabricIndex(defaultFabricName);
	msg.append("Fabric index : " + to_string(fabricIndex) + "\n");

	int defaultFabricIndex = 0;
	string fabricName = FABRIC_API->GetFabricName(defaultFabricIndex);
	msg.append("Fabric name : " + fabricName + "\n");

	UTILITY_API->DisplayMessageBox(msg);
}

void ChangeFabricWithJson_Sample()
{
	if (!FABRIC_API || !UTILITY_API)
		return;

	int defaultFabricIndex = 0;

	string baseFolder = getHomePath() + "fabric/";
	string testJsonPath = baseFolder + "fabric_test.json";
	bool bResult = FABRIC_API->ChangeFabricWithJson(defaultFabricIndex, testJsonPath);

	if (bResult)
		UTILITY_API->DisplayMessageBox("Failed to change fabric with JSON.");
	else
		UTILITY_API->DisplayMessageBox("Complete to change fabric with JSON.");
}

void AssignFabricToPattern_Sample()
{
	if (!FABRIC_API || !UTILITY_API)
		return;

	// Assign Fabric #0 to the pattern #0
	int defaultFabricIndex = 0;
	int defaultPatternIndex = 0;
	bool bResult = FABRIC_API->AssignFabricToPattern(defaultFabricIndex, defaultPatternIndex, 1);

	if(bResult)
		UTILITY_API->DisplayMessageBox("Complete to assign fabric to pattern.");		
	else
		UTILITY_API->DisplayMessageBox("Failed to assign fabric to pattern.");
}

void ImportZprj_Sample()
{
	if (!IMPORT_API)
		return;

	string baseFolder = getHomePath() + "Zpac/";
	string filePath = baseFolder + "test.zprj"; //must assign correct file path

	Marvelous::ImportZPRJOption option;
	IMPORT_API->ImportZprj(filePath, option);
}

void ImportFile_Sample()
{
	if (!IMPORT_API)
		return;

	string baseFolder = getHomePath() + "Zpac/";
	string filePath = baseFolder + "test.zprj"; //must assign correct file path

	IMPORT_API->ImportFile(filePath);
}

void Set3DGarmentRenderingStyle_Sample() {
	if (!UTILITY_API)
		return;


	// Set 3D view garment rendering style
	UTILITY_API->Set3DGarmentRenderingStyle(0);
	UTILITY_API->DisplayMessageBox("Textured Surface");

	UTILITY_API->Set3DGarmentRenderingStyle(1);
	UTILITY_API->DisplayMessageBox("Thick Textured Surface");

	UTILITY_API->Set3DGarmentRenderingStyle(2);
	UTILITY_API->DisplayMessageBox("Monochrome Surface");

	UTILITY_API->Set3DGarmentRenderingStyle(3);
	UTILITY_API->DisplayMessageBox("Translucent Surface");

	UTILITY_API->Set3DGarmentRenderingStyle(4);
	UTILITY_API->DisplayMessageBox("Mesh");

	UTILITY_API->Set3DGarmentRenderingStyle(5);
	UTILITY_API->DisplayMessageBox("Thick Textured Surface (Back)");

	UTILITY_API->Set3DGarmentRenderingStyle(6);
	UTILITY_API->DisplayMessageBox("Random Color Surface");

}

void ExportZpac_Test()
{
	if (!EXPORT_API || !UTILITY_API)
		return;

	string exportPath = EXPORT_API->ExportZPac();

	string msg = "Export ZPac Complete: " + exportPath;
	UTILITY_API->DisplayMessageBox(msg);
}

void GetAvatarCount_Test()
{
	if (!EXPORT_API || !UTILITY_API)
		return;

	unsigned int avatarCnt = EXPORT_API->GetAvatarCount();

	string msg = "Avatar Count : " + to_string(avatarCnt);
	UTILITY_API->DisplayMessageBox(msg);
}

void GetAvatarNameList_Test()
{
	if (!EXPORT_API || !UTILITY_API)
		return;

	vector<string> avatarNameList = EXPORT_API->GetAvatarNameList();

	string msg = "Avatar Name List : ";
	for (size_t i = 0; i < avatarNameList.size(); ++i)
		msg = msg + avatarNameList[i] + "\n";

	UTILITY_API->DisplayMessageBox(msg);
}

void GetAvatarGenderList_Test()
{
	if (!EXPORT_API || !UTILITY_API)
		return;

	vector<int> avatarGenderList = EXPORT_API->GetAvatarGenderList();

	string msg = "Avatar Gender List : ";
	for (size_t i = 0; i < avatarGenderList.size(); ++i)
	{
		if (avatarGenderList[i] == 0)
			msg = msg + "male" + "\n";
		else if (avatarGenderList[i] == 1)
			msg = msg + "female" + "\n";
		else
			msg = msg + "unknown" + "\n";
	}

	UTILITY_API->DisplayMessageBox(msg);
}

void GetPatternIndex_Test()
{
	// prior to calling this function.
	// please set the appropriate pattern name to "Test API Pattern" in the CLO software
	if (!PATTERN_API || !UTILITY_API)
		return;

	string patternName = "Test API Pattern";
	unsigned int patternIndex = PATTERN_API->GetPatternIndex(patternName);

	string msg = "Index of Test API Pattern : " + to_string(patternIndex);
	UTILITY_API->DisplayMessageBox(msg);
}

void GetPatternCount_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	unsigned int patternCnt = PATTERN_API->GetPatternCount();

	string msg = "Pattern Count : " + to_string(patternCnt);
	UTILITY_API->DisplayMessageBox(msg);
}

void GetMajorVersion_Test()
{
	if (!UTILITY_API)
		return;

	unsigned int majorVer = UTILITY_API->GetMajorVersion();

	string msg = "Major Version of CLO : " + to_string(majorVer);
	UTILITY_API->DisplayMessageBox(msg);
}

void GetMinorVersion_Test()
{
	if (!UTILITY_API)
		return;

	unsigned int minorVer = UTILITY_API->GetMinorVersion();

	string msg = "Minor Version of CLO : " + to_string(minorVer);
	UTILITY_API->DisplayMessageBox(msg);
}

void GetPatchVersion_Test()
{
	if (!UTILITY_API)
		return;

	unsigned int patchVer = UTILITY_API->GetPatchVersion();

	string msg = "Patch Version of CLO : " + to_string(patchVer);
	UTILITY_API->DisplayMessageBox(msg);
}

void ExportGLB_Sample()
{
	if (!EXPORT_API)
		return;

	Marvelous::ImportExportOption options;
	options.bExportAvatar = false;
	options.bExportGarment = true;
	options.bSaveInZip = false;
	options.scale = 0.001f; // same as gltf scale

	// the other options are given as default. please refer to ImportExportOption class in ExportAPI.h

	vector<string> exportedFilePathList;
	string baseFolder = getHomePath() + "export_glb/";
	exportedFilePathList = EXPORT_API->ExportGLB(baseFolder + "test.glb", options); // returns only a file path for GLB file 

	for (auto& path : exportedFilePathList)
	{
		if (UTILITY_API)
			UTILITY_API->DisplayMessageBox(path);
	}
}

void SaveFabricCustomThumbnail_Sample()
{
	if (!UTILITY_API)
		return;

	// sample fabric file
	std::string fabricFilePath = "C:/Zpac/Silk_Chiffon.zfab";
	
	// icon thumbnail
	unsigned int fileSize = 0;

	unsigned char* icoBuffer = UTILITY_API->GetAssetIconInCLOFile(fabricFilePath, fileSize);

	if (icoBuffer != nullptr && fileSize > 0)
	{
		FILE* saveFp = fopen("C:/Zpac/fabric_icon_thumbnail.png", "wb");
		fwrite((const void*)icoBuffer, 1, fileSize, saveFp);
		fclose(saveFp);
	}

	// custom thumbnails
	unsigned int fileSize1 = 0;
	unsigned int fileSize2 = 0;

	unsigned char* buffer1 = UTILITY_API->GetThumbnailInCLOFile(fabricFilePath, 0, fileSize1);
	unsigned char* buffer2 = UTILITY_API->GetThumbnailInCLOFile(fabricFilePath, 1, fileSize2);

	if (buffer1 != nullptr && fileSize1 > 0)
	{
		FILE* saveFp = fopen("C:/Zpac/fabric_custom_thumbnail1.png", "wb");
		fwrite((const void*)buffer1, 1, fileSize1, saveFp);
		fclose(saveFp);
	}

	if (buffer2 != nullptr && fileSize2 > 0)
	{
		FILE* saveFp = fopen("C:/Zpac/fabric_custom_thumbnail2.png", "wb");
		fwrite((const void*)buffer2, 1, fileSize2, saveFp);
		fclose(saveFp);
	}
}

void ImportOBJ_Sample()
{
	if (!IMPORT_API)
		return;

	string baseFolder = getHomePath() + "Zpac/";
	string filePath = baseFolder + "test.zip";

	Marvelous::ImportExportOption options;

	options.bAutoTranslate = false;
	options.bAddArrangementPoints = false;
	options.bAutoCreateFittingSuit = false;
	options.bAdd = false;

	options.scale = 1.0f;

	options.axisX = 0;
	options.axisY = 1;
	options.axisZ = 2;

	options.bInvertX = false;
	options.bInvertY = false;
	options.bInvertZ = false;

	options.ImportObjectType = 0;

	options.translationValueX = 0.0f;
	options.translationValueY = 0.0f;
	options.translationValueZ = 0.0f;

	options.bTrace2DPatternsUVMap = false;

	IMPORT_API->ImportOBJ(filePath, options);
}

void ImportVMP_Sample()
{
	if (!IMPORT_API)
		return;

	string baseFolder = getHomePath() + "VRay/";
	string filePath = baseFolder + "test.vmp";

	IMPORT_API->ImportVMP(filePath);
}

void ImportCPT_Sample()
{
	if (!IMPORT_API)
		return;

	string baseFolder = getHomePath() + "VRay/";
	string filePath = baseFolder + "test.cpt";

	IMPORT_API->ImportCPT(filePath);
}

void ImportVLP_Sample()
{
	if (!IMPORT_API)
		return;

	string baseFolder = getHomePath() + "VRay/";
	string filePath = baseFolder + "test.vlp";

	IMPORT_API->ImportVLP(filePath);
}

void ImportVRP_Sample()
{
	if (!IMPORT_API)
		return;

	string baseFolder = getHomePath() + "VRay/";
	string filePath = baseFolder + "test.vrp";

	IMPORT_API->ImportVRP(filePath);
}

void UpdateFabricInformation_Sample()
{
	if (!FABRIC_API)
		return;

	string baseFolder = getHomePath() + "fabric/";
	string filePath = baseFolder + "test.zfab";
	string customImgPath = baseFolder + "customImg.png";

	unsigned int fabricIndex = FABRIC_API->AddFabric(filePath);

	std::map<string, string> fabricInfoMap;
	fabricInfoMap.insert(make_pair("SupplierName", "Bill"));
	fabricInfoMap.insert(make_pair("Owner", "John"));

	FABRIC_API->SetFabricInformation(fabricIndex, fabricInfoMap);
	FABRIC_API->SetCustomImage(fabricIndex, customImgPath);

	string outputFilePath = baseFolder + "output.zfab";
	FABRIC_API->ExportZFab(outputFilePath, fabricIndex);
}

void GetPrimaryFabric_Sample()
{
	if (FABRIC_API == nullptr || UTILITY_API == nullptr)
		return;

	int primaryFabricIndex = FABRIC_API->GetPrimaryFabric();

	UTILITY_API->DisplayMessageBox(to_string(primaryFabricIndex));
}

void GetColorListForColorWay_Sample()
{
	if (UTILITY_API == nullptr)
		return;

	unsigned int colorwayIndex = 2;
	vector<Marvelous::CloApiRgba> colorList = UTILITY_API->GetColorListForColorWay(colorwayIndex);

	string msg = "Colorway Index #" + to_string(colorwayIndex) + " Color List\n--------------------------------------\n";
	for (size_t i = 0; i < colorList.size(); ++i)
		msg = msg + "R" + to_string(colorList[i].R) + " " + "G" + to_string(colorList[i].G) + " " + "B" + to_string(colorList[i].B) + " " + "A" + to_string(colorList[i].A) + "\n";

	UTILITY_API->DisplayMessageBox(msg);
}

void ExportPOM_Sample()
{
	if (!EXPORT_API)
		return;	
	
	string baseFolder = getHomePath() + "export_pom/";
	string exportedFilePath = EXPORT_API->ExportPOM(baseFolder + "test.csv");

	if (UTILITY_API)
		UTILITY_API->DisplayMessageBox(exportedFilePath);
}

void ExportPOMfor3DLength_Sample()
{
	if (!EXPORT_API)
		return;

	string baseFolder = getHomePath() + "export_pom/";
	string exportedFilePath = EXPORT_API->ExportPOM(true, baseFolder + "test.csv");

	if (UTILITY_API)
		UTILITY_API->DisplayMessageBox(exportedFilePath);
}

void SetShowHideAvatar_Sample()
{
	if (UTILITY_API == nullptr)
		return;

	UTILITY_API->SetShowHideAvatar(true); // true : show / false : hide
}

void SetShowHideAvatarByIndex_Sample()
{
	if (UTILITY_API == nullptr || EXPORT_API == nullptr)
		return;

	unsigned int avatarCnt = EXPORT_API->GetAvatarCount();
	if (avatarCnt == 0)
		return;

	UTILITY_API->SetShowHideAvatar(true, avatarCnt - 1);

}

void IsShowAvatarByIndex_Sample()
{
	if (UTILITY_API == nullptr || EXPORT_API == nullptr)
		return;

	unsigned int avatarCnt = EXPORT_API->GetAvatarCount();
	if (avatarCnt == 0)
		return;

	bool bShow = UTILITY_API->IsShowAvatar(avatarCnt - 1);

	string msg = "Is Avatar(Index: " + to_string(avatarCnt - 1) + ")'s Shown? -" + to_string(bShow);
	UTILITY_API->DisplayMessageBox(msg);
}

void SetSchematicRender_Sample()
{
	if (UTILITY_API == nullptr)
		return;

	bool schematicRenderStatus = UTILITY_API->GetSchematicRender();
	string msg = "Current Schematic Render Status : " + to_string(schematicRenderStatus);
	UTILITY_API->DisplayMessageBox(msg);

	UTILITY_API->SetSchematicRender(true); // true : enable / false : disable
}

void GetPatternPieceArea_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	float area = PATTERN_API->GetPatternPieceArea(0);

	string msg = "Pattern Piece Area : " + to_string(area);
	UTILITY_API->DisplayMessageBox(msg);
}

void GetLineLength_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	float length = PATTERN_API->GetLineLength(0, 0);

	string msg = "Line Length : " + to_string(length);
	UTILITY_API->DisplayMessageBox(msg);
}

void GetPatternInputInformation_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	string msg = PATTERN_API->GetPatternInputInformation();	
	UTILITY_API->DisplayMessageBox(msg);
}

void GetBoundingBoxOfPattern_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	std::map<string, string> infoMap = PATTERN_API->GetBoundingBoxOfPattern(0);

	string msg = "";

	for (std::map<string, string>::const_iterator iter = infoMap.cbegin(); iter != infoMap.cend(); ++iter)
	{
		msg.append(iter->first + " : " + iter->second + "\n");
	}

	UTILITY_API->DisplayMessageBox(msg);
}

void GetBoundingBoxOfPatterns_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	vector<std::map<string, string>> infoVmap = PATTERN_API->GetBoundingBoxOfPattern();

	string msg = "";

	for (auto& infoMap : infoVmap)
	{
		for (std::map<string, string>::const_iterator iter = infoMap.cbegin(); iter != infoMap.cend(); ++iter)
		{
			msg.append(iter->first + " : " + iter->second + "\n");
		}
	}

	UTILITY_API->DisplayMessageBox(msg);
}

void GetParticleDistanceOfPattern_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	float particleDistance = PATTERN_API->GetParticleDistanceOfPattern(0);
	
	string msg = "Pattern Particle Distance :" + to_string(particleDistance);
	UTILITY_API->DisplayMessageBox(msg);

}

void GetMeshCountByType_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	std::map<string, string> infoMap = PATTERN_API->GetMeshCountByType(0);

	string msg = "";
 
 	for (std::map<string, string>::const_iterator iter = infoMap.cbegin(); iter != infoMap.cend(); ++iter)
 	{
 		msg.append(iter->first + " : " + iter->second + "\n");
 	}

 	UTILITY_API->DisplayMessageBox(msg);
}

void GetShrinkagePercentage_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	std::map<string, string> infoMap = PATTERN_API->GetShrinkagePercentage(0);

	string msg = "";

	for (std::map<string, string>::const_iterator iter = infoMap.cbegin(); iter != infoMap.cend(); ++iter)
	{
		msg.append(iter->first + " : " + iter->second + "\n");
	}

	UTILITY_API->DisplayMessageBox(msg);
}

void ImportDXFFile_Sample()
{
	if (!IMPORT_API)
		return;

	string baseFolder = getHomePath() + "DXF/";
	string filePath = baseFolder + "test.dxf";

	Marvelous::ImportDxfOption option;
	option.m_bAppend = false;
	IMPORT_API->ImportDXF(filePath, option);
}

void SetFabricName_Sample()
{
	if (!FABRIC_API)
		return;

	// current fabric index
	unsigned int currentFabricIndex = FABRIC_API->GetCurrentFabricIndex();
	string msg = "Current Fabric Index: " + to_string(currentFabricIndex);
	UTILITY_API->DisplayMessageBox(msg);

	// fabric name
	string currentName = FABRIC_API->GetFabricName(currentFabricIndex);
	currentName = "Current Fabric Name: " + currentName;
	UTILITY_API->DisplayMessageBox(currentName);

	// set fabric name
	string newName = "APITEST_Current_Fabric_Name";
	FABRIC_API->SetFabricName(currentFabricIndex, newName);
	currentName = "Current Fabric Name: " + newName;
	UTILITY_API->DisplayMessageBox(currentName);
}

void UpdateColorways_Sample()
{
	if (!UTILITY_API)
		return;

	bool bIgnoreCurrentMode = true;

	UTILITY_API->UpdateColorways(bIgnoreCurrentMode);
}

void ExportThumbnail3DForColorways_Sample()
{
	if (!EXPORT_API)
		return;

	unsigned int targetIndex = 0;

	string savedPath = EXPORT_API->ExportThumbnail3DByColorwayIndex(targetIndex);

	UTILITY_API->DisplayMessageBox(savedPath);
}

void SetParticleDistanceOfPattern_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetParticleDistanceOfPattern(0,0.0f);
}

void SetParticleDistanceOfPatterns_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetParticleDistanceOfPatterns(0.0f);
}

void SetMeshTypeOfPattern_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetMeshType(0, "Triangle");
}

void SetWidthShrinkagePercentageOfPattern_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetWidthShrinkagePercentage(0, 0.1f);
}

void SetHeightShrinkagePercentageOfPattern_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetHeightShrinkagePercentage(0, 0.1f);
}

void GetArrangementList_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	vector<std::map<string, string>> infoVmap = PATTERN_API->GetArrangementList();

	string msg = "";

	for (auto& infoMap : infoVmap)
	{
		for (std::map<string, string>::const_iterator iter = infoMap.cbegin(); iter != infoMap.cend(); ++iter)
		{
			msg.append(iter->first + " : " + iter->second + "\n");
		}
	}

	if (infoVmap.empty())
	{
		msg = "Arrangement List is Empty";
	}

	UTILITY_API->DisplayMessageBox(msg);
}

void GetArrangementOfPattern_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;
	
	std::map<string, string> infoMap = PATTERN_API->GetArrangementOfPattern(0);

	string msg = "";

	for (std::map<string, string>::const_iterator iter = infoMap.cbegin(); iter != infoMap.cend(); ++iter)
	{
		msg.append(iter->first + " : " + iter->second + "\n");
	}

	UTILITY_API->DisplayMessageBox(msg);
}

void GetArrangementOfPatterns_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	vector<std::map<string, string>> infoVmap = PATTERN_API->GetArrangementOfPattern();

	string msg = "";

	for (auto& infoMap : infoVmap)
	{
		for (std::map<string, string>::const_iterator iter = infoMap.cbegin(); iter != infoMap.cend(); ++iter)
		{
			msg.append(iter->first + " : " + iter->second + "\n");
		}
	}

	if (infoVmap.empty())
	{
		msg = "Arrangement List is Empty";
	}

	UTILITY_API->DisplayMessageBox(msg);
}

void SetArrangementShapeStyle_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetArrangementShapeStyle(0, "Flat");
}

void SetArrangementPosition_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetArrangementPosition(0, 0, 0, 0);
}

void SetArrangementOrientation_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetArrangementOrientation(0, 0);
}

void SetArrangement_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetArrangement(0, 0);
}

void ExportAvatarPose_Test()
{
	string exportPath = getHomePath() + "export_Pose/test.pos";
	string resultPath = "";

	if (EXPORT_API)
		resultPath = EXPORT_API->ExportPose(exportPath);

	UTILITY_API->DisplayMessageBox(resultPath);
}

void ExportFBX_Test()
{
	if (!EXPORT_API)
		return;

	Marvelous::ImportExportOption options;
	options.bExportAvatar = true;
	options.bExportGarment = true;
	// the other options are given as default. please refer to ImportExportOption class in ExportAPI.h

	vector<string> exportedFilePathList;
	string baseFolder = getHomePath() + "export_fbx/";
	exportedFilePathList = EXPORT_API->ExportFBX(baseFolder + "test.fbx", options);

	for (const auto& path : exportedFilePathList)
	{
		if (UTILITY_API)
			UTILITY_API->DisplayMessageBox(path);
	}
}

void DeleteColorwayItem_Test()
{
	if (UTILITY_API == nullptr)
		return;

	unsigned int targetIndex = 0;

	UTILITY_API->DeleteColorwayItem(targetIndex);

	UTILITY_API->UpdateColorways();
}

void CopyPatternPiecePos_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	int patternIndex = -1;
	patternIndex = PATTERN_API->CopyPatternPiecePos(0, 100.0f, 100.0f);
	
	string msg = "Copy Pattern Index : " + to_string(patternIndex);
	UTILITY_API->DisplayMessageBox(msg);
}

void CopyPatternPieceMove_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	int patternIndex = -1;
	patternIndex = PATTERN_API->CopyPatternPieceMove(0, 100.0f, 100.0f);

	string msg = "Copy Pattern Index : " + to_string(patternIndex);
	UTILITY_API->DisplayMessageBox(msg);
}

void DeletePatternPiece_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->DeletePatternPiece(0);
}

void DeleteLine_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	//라인이 5개 이상 있어야 동작, 5개 미만이면 패턴삭제
	PATTERN_API->DeleteLine(0, 0);
}

void DeletePoint_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	//점이 3개이상 있어야 동작. 3개 미만이면 패턴삭제
	PATTERN_API->DeletePoint(0, 0);
}

void FlipPatternPiece_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	//월드좌표 기준으로 가로 Flip
	PATTERN_API->FlipPatternPiece(0, true, false);
}

void LayerClonePatternPiecePos_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;
	
	PATTERN_API->LayerClonePatternPiecePos(0, 100.0f, 100.0f, true);
}

void LayerClonePatternPieceMove_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;
	
	PATTERN_API->LayerClonePatternPieceMove(0, 100.0f, 100.0f, true);
}
   
void ElasticTest()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternPieceElastic(0, -1, true);
	PATTERN_API->SetPatternPieceElastic(1, 2, true);
}
void ElasticStrengthTest()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternPieceElastic(0, -1, true);
	PATTERN_API->SetPatternPieceElasticStrength(0, -1, 50.0);
	PATTERN_API->SetPatternPieceElasticStrength(1, 1, 80.0);

}
void ElasticStrengthRatioTest()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternPieceElastic(0, -1, true);
	PATTERN_API->SetPatternPieceElasticStrengthRatio(0, -1, 60);
	PATTERN_API->SetPatternPieceElasticStrengthRatio(1, 1, 80);
}
void ElasticSegmentLengthTest()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternPieceElastic(0, -1, true);
	PATTERN_API->SetPatternPieceElasticSegmentLength(0, -1, 200.0);
	PATTERN_API->SetPatternPieceElasticSegmentLength(1, 1, 300.0);
}
void ElasticTotalLengthTest() 
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternPieceElastic(0, -1, true);
	PATTERN_API->SetPatternPieceElasticTotalLength(0, -1, 200.0);
	PATTERN_API->SetPatternPieceElasticTotalLength(1, 1, 300.0);
}
void ShirringTest()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternPieceShirring(0, -1, true);
	PATTERN_API->SetPatternPieceShirring(1, 1, true);
}
void ShirringIntervalTest()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternPieceShirring(0, -1, true);
	PATTERN_API->SetPatternPieceShirringInterval(0, -1, 15.0);
	PATTERN_API->SetPatternPieceShirringInterval(1, 1, 15.0);
}
void ShirringHeightTest()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternPieceShirring(0, -1, true);
	PATTERN_API->SetPatternPieceShirringHeight(0, -1, 20.0);
	PATTERN_API->SetPatternPieceShirringHeight(1, 1, 20.0);
}
void ShirringExtendTest()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternPieceShirring(0, -1, true);
	PATTERN_API->SetPatternPieceShirringExtend(0, -1, true);
	PATTERN_API->SetPatternPieceShirringExtend(1, 1, true);
}
void SeamTapingTest()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternPieceSeamtaping(0, -1, true);
	PATTERN_API->SetPatternPieceSeamtaping(1, 1, true);
}
void SeamTapingWidthTest()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternPieceSeamtaping(0, -1, true);
	PATTERN_API->SetPatternPieceSametapingWidth(0, -1, 44.0);
	PATTERN_API->SetPatternPieceSametapingWidth(1, 1, 33.0);
}

void OffsetAsInternalLine_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;
	
	PATTERN_API->OffsetAsInternalLine(0, 0, 1, 100, false, true);
}

void UnfoldPatternPiece_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	//0번라인 기준으로 하프시메트리 패턴으로 생성
	PATTERN_API->UnfoldPatternPiece(0, 0, true);
}

void ConvertToBaseLine_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;
	
	//첫번째 자식이 내부도형이어야만 동작함.
	PATTERN_API->ConvertToBaseLine(0, 0);
}

void ConvertToInternalLine_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	//두번째 자식이 기초선이어야만 동작함.
	PATTERN_API->ConvertToInternalLine(0, 1);
}

void DistribueInternalLinesbetweenSegments_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	vector<int> lineIndexs;
	lineIndexs.push_back(0);
	lineIndexs.push_back(2);

	//선분이 4개이상이어야 동작. 기본옵션 3개, 곡선으로, 반전안함, 연장
	PATTERN_API->DistribueInternalLinesbetweenSegments(0, lineIndexs, 3, false, false, true );
}

void ImportGraphicStyle_Test()
{
	if (IMPORT_API == nullptr)
		return;

	string baseFolder = getHomePath() + "graphic_style/";
	string testFile = "test_1.png";
	string fullPath = baseFolder + testFile;

	IMPORT_API->ImportGraphicStyleFromImage(fullPath);
}

void ReplaceGraphicStyle_Test()
{
	if (UTILITY_API == nullptr)
		return;

	string baseFolder = getHomePath() + "graphic_style/";
	string testFile = "test_2.jpg";
	string fullPath = baseFolder + testFile;

	int anchor = 0;

	UTILITY_API->ReplaceGraphicStyleFromImage(0, fullPath, anchor);
}

void GetPatternPiecePosTest()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

		std::vector<float> res = PATTERN_API->GetPatternPiecePos(0);

		if(res.empty())
			return;
			
		float xPos = res[0];
		float yPos = res[1];
}
	
void SetPatternPiecePosTest()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternPiecePos(0, 100.0, 100.0);
}

void SetPatternPieceMoveTest()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternPieceMove(0, 100.0, 100.0);
}

void PatternPieceInfo_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;
	int patternPieceIndex = 0;
	UTILITY_API->DisplayMessageBox("Current Pattern Piece Name : " + PATTERN_API->GetPatternPieceName(patternPieceIndex));
	PATTERN_API->SetPatternPieceName(patternPieceIndex, "set_name_example");
	UTILITY_API->DisplayMessageBox("Changed Pattern Piece Name : " + PATTERN_API->GetPatternPieceName(patternPieceIndex));

	UTILITY_API->DisplayMessageBox("Current Pattern Piece Category : " + to_string(PATTERN_API->GetPatternPieceCategory(patternPieceIndex)));
	PATTERN_API->SetPatternPieceCategory(patternPieceIndex, 1);
	int data = PATTERN_API->GetPatternPieceCategory(patternPieceIndex);
	UTILITY_API->DisplayMessageBox("Changed Pattern Piece Category : " + to_string(data));

	string classification = PATTERN_API->GetPatternPieceClassification(patternPieceIndex);
	UTILITY_API->DisplayMessageBox("Current Pattern Piece Classification :" + classification);
	PATTERN_API->SetPatternPieceClassification(patternPieceIndex, "Binding");
	UTILITY_API->DisplayMessageBox("Changed Pattern Piece Classification :" + PATTERN_API->GetPatternPieceClassification(patternPieceIndex));
}

void PatternPieceFabricStyleInfo_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;
	int patternPieceIndex = 0;
	UTILITY_API->DisplayMessageBox("Current Fabric Style Index : " + to_string(PATTERN_API->GetPatternPieceFabricIndex(patternPieceIndex)));
	PATTERN_API->SetPatternPieceFabricIndex(0, 1);
	UTILITY_API->DisplayMessageBox("Changed Fabric Style Index :" + to_string(PATTERN_API->GetPatternPieceFabricIndex(patternPieceIndex)));

	UTILITY_API->DisplayMessageBox("Current Grain Direction : " + to_string(PATTERN_API->GetPatternPieceGrainDirection(patternPieceIndex)));
	PATTERN_API->SetPatternPieceGrainDirection(patternPieceIndex, 50.0f);
	UTILITY_API->DisplayMessageBox("Changed Grain Direction : " + to_string(PATTERN_API->GetPatternPieceGrainDirection(patternPieceIndex)));

	bool isOn = PATTERN_API->IsPatternPieceGrainLinkAllColorways(patternPieceIndex);
	string curr = isOn ? "On" : "Off";
	UTILITY_API->DisplayMessageBox("Current Grain Link All Colorway : " + curr);
	PATTERN_API->SetPatternPieceGrainLinkAllColorways(0, isOn ? false : true);
	string update = PATTERN_API->IsPatternPieceGrainLinkAllColorways(patternPieceIndex) ? "On" : "Off";
	UTILITY_API->DisplayMessageBox("Changed Grain Link All Colorway : " + update);
}

void GetPatternPieceSolidifyInfo_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;
	int patternPieceIndex = 0;
	string curr = PATTERN_API->IsPatternPieceSolidify(patternPieceIndex) ? "ON" : "OFF";
	UTILITY_API->DisplayMessageBox("Current Solidify : " + curr);
	PATTERN_API->SetPatternPieceSolidify(0, true);
	curr = PATTERN_API->IsPatternPieceSolidify(patternPieceIndex) ? "ON" : "OFF";
	UTILITY_API->DisplayMessageBox("Changed Solidify :" + curr);

	UTILITY_API->DisplayMessageBox("Current Solidify Stregthen : " + to_string(PATTERN_API->GetPatternPieceSolidifyStrengthen(patternPieceIndex)));
	PATTERN_API->SetPatternPieceSolidifyStrengthen(patternPieceIndex, 200000.0f);
	UTILITY_API->DisplayMessageBox("Changed Solidify Stregthen : " + to_string(PATTERN_API->GetPatternPieceSolidifyStrengthen(patternPieceIndex)));
}

void GetFabricStyleNameList_Test()
{
	if (!FABRIC_API || !UTILITY_API)
		return;
	int patternPieceIndex = 0;
	vector<string> fabricList = FABRIC_API->GetFabricStyleNameList();
	string strFabricList = to_string(fabricList.size()) + "\n";
	for (int i = 0; i < fabricList.size(); ++i)
	{
		strFabricList += fabricList[i] + "\n";
	}
	UTILITY_API->DisplayMessageBox(strFabricList);
}

void SetPatternLayer_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternLayer(0, 1);
}

void GetPatternLayer_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	int patternLayer = PATTERN_API->GetPatternLayer(0);

	string msg = "Pattern Layer :" + to_string(patternLayer);
	UTILITY_API->DisplayMessageBox(msg);
	
}

void SetPatternStrengthen_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternStrengthen(0, true);
}

void SetPatternLock_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternLock(0, true);
}

void SetPatternHide3D_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternHide3D(0, true);
}

void SetPatternFreeze_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternFreeze(0, true);
}

void AddSegmentTopstitch_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	string msg = "";

	bool bAdd = PATTERN_API->AddSegmentTopstitch(0, 0, 0);

	if (bAdd == false)
	{
		msg = "Add Segment Topstitch is Fail.";
		UTILITY_API->DisplayMessageBox(msg);
	}

}

void GetTopstitchStyleList_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	vector<std::map<string, string>> infoVmap = PATTERN_API->GetTopstitchStyleList();

	string msg = "";

	for (auto& infoMap : infoVmap)
	{
		for (std::map<string, string>::const_iterator iter = infoMap.cbegin(); iter != infoMap.cend(); ++iter)
		{
			msg.append(iter->first + " : " + iter->second + "\n");
		}
	}

	if (infoVmap.empty())
	{
		msg = "Topstitch Style List is Empty";
	}

	UTILITY_API->DisplayMessageBox(msg);
}

void GetPatternAssignedTopstitchCount_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	int topstitchCnt = PATTERN_API->GetPatternAssignedTopstitchCount(0);

	string msg = "Pattern Topstitch Count : " + to_string(topstitchCnt);
	UTILITY_API->DisplayMessageBox(msg);

}

void GetPatternAssignedTopstitchStyle_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	vector<std::map<string, string>> infoVmap = PATTERN_API->GetPatternAssignedTopstitchStyle(0);

	string msg = "";

	for (auto& infoMap : infoVmap)
	{
		for (std::map<string, string>::const_iterator iter = infoMap.cbegin(); iter != infoMap.cend(); ++iter)
		{
			msg.append(iter->first + " : " + iter->second + "\n");
		}
	}

	if (infoVmap.empty())
	{
		msg = "Topstitch Style List is Empty";
	}

	UTILITY_API->DisplayMessageBox(msg);
}

void GetPatternAssignedTopstitch_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	vector<std::map<string, string>> infoVmap = PATTERN_API->GetPatternAssignedTopstitch(0);

	string msg = "";

	for (auto& infoMap : infoVmap)
	{
		for (std::map<string, string>::const_iterator iter = infoMap.cbegin(); iter != infoMap.cend(); ++iter)
		{
			msg.append(iter->first + " : " + iter->second + "\n");
		}
	}

	if (infoVmap.empty())
	{
		msg = "Topstitch List is Empty";
	}

	UTILITY_API->DisplayMessageBox(msg);
}

void GetPatternAssignedTopstitchStyleIndex_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	int topstitchStyleIndex = PATTERN_API->GetPatternAssignedTopstitchStyleIndex(0,0);

	string msg = "Pattern Topstitch StyleIndex : " + to_string(topstitchStyleIndex);
	UTILITY_API->DisplayMessageBox(msg);

}

void SetPatternAssignedTopstitchStyle_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternAssignedTopstitchStyle(0, 0, 0);
}

void IsPatternAssignedTopstitchExtendStart_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	bool extendStart = PATTERN_API->IsPatternAssignedTopstitchExtendStart(0, 0);

	string msg = "Pattern Topstitch Extend Start: " + to_string(extendStart);
	UTILITY_API->DisplayMessageBox(msg);

}

void SetPatternAssignedTopstitchExtendStart_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternAssignedTopstitchExtendStart(0, 0, false);

}

void IsPatternAssignedTopstitchExtendEnd_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	bool extendEnd = PATTERN_API->IsPatternAssignedTopstitchExtendEnd(0, 0);

	string msg = "Pattern Topstitch Extend End: " + to_string(extendEnd);
	UTILITY_API->DisplayMessageBox(msg);

}

void SetPatternAssignedTopstitchExtendEnd_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternAssignedTopstitchExtendEnd(0, 0, false);

}

void IsPatternAssignedTopstitchCurved_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	bool curved = PATTERN_API->IsPatternAssignedTopstitchCurved(0, 0);

	string msg = "Pattern Topstitch Curved : " + to_string(curved);
	UTILITY_API->DisplayMessageBox(msg);

}

void SetPatternAssignedTopstitchCurved_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternAssignedTopstitchCurved(0, 0, false);

}

void GetPatternAssignedTopstitchCurvedLength_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	int curved = PATTERN_API->GetPatternAssignedTopstitchCurvedLength(0, 0);

	string msg = "Pattern Topstitch Curved Length : " + to_string(curved);
	UTILITY_API->DisplayMessageBox(msg);

}

void SetPatternAssignedTopstitchCurvedLength_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternAssignedTopstitchCurvedLength(0, 0, 0);

}

void IsPatternAssignedTopstitchCurvedRightAngled_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	bool curved = PATTERN_API->IsPatternAssignedTopstitchCurvedRightAngled(0, 0);

	string msg = "Pattern Topstitch Curved : " + to_string(curved);
	UTILITY_API->DisplayMessageBox(msg);

}

void SetPatternAssignedTopstitchCurvedRightAngled_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternAssignedTopstitchCurvedRightAngled(0, 0, false);

}

void GetPatternAssignedTopstitchZOffset_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	float zoffset = PATTERN_API->GetPatternAssignedTopstitchZOffset(0, 0);

	string msg = "Pattern Topstitch Zoffset : " + to_string(zoffset);
	UTILITY_API->DisplayMessageBox(msg);

}

void SetPatternAssignedTopstitchZOffset_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	PATTERN_API->SetPatternAssignedTopstitchZOffset(0, 0, 0.0f);

}

void ImportTopStitchStyle_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	string baseFolder = getHomePath() + "stitch/";
	string sstFilePath = baseFolder + "test.sst";
	string msg = "";

	bool bAdd = PATTERN_API->ImportTopStitchStyle(sstFilePath);

	if (bAdd == false)
	{
		msg = "Import Topstitch Style is Fail.";
		UTILITY_API->DisplayMessageBox(msg);
	}
}

void ImportAVAC_Sample()
{
	string baseFolder = getHomePath() + "Zpac/Avatar/";
	string avatarPath = baseFolder + "ASD-GGLE012-1902_STD_Basic_v1.0.0.2.avac";
	//input you are apf file path
	string apfFilePath = baseFolder + "CLO Virtual Fashion Inc. (2022-06-17 05-08-05 UTC).apf";
	IMPORT_API->ImportAVAC(avatarPath, apfFilePath);
}

void SetAvatarBodyTexture_Sample()
{
	//first of all, need to load avatar in clo
	wstring bodyShapeName = L"body";
	string path = getHomePath() + "ZPac/Texture/";
	wstring textureFullPath = L"ZPac/Texture/";

	textureFullPath.assign(path.begin(), path.end());
	vector<wstring> pathList;

	//If you want to use the list to change everything, you have to keep the index well.
	wstring wPath = textureFullPath + L"HumanLike_lambert1_Normal.1001.png";
	pathList.push_back(wPath);
	wPath = textureFullPath + L"HumanLike_lambert1_Normal.1001.png";
	pathList.push_back(wPath);
	wPath = textureFullPath + L"HumanLike_lambert1_Normal.1001.png";
	pathList.push_back(wPath);
	wPath = textureFullPath + L"HumanLike_lambert1_Normal.1001.png";
	pathList.push_back(wPath);

	//0: face, 1:body, 2:arm 3:leg
	for (int matMeshIndex = 0; matMeshIndex < pathList.size(); ++matMeshIndex)
	{
		UTILITY_API->SetAvatarMeshTexture(bodyShapeName, matMeshIndex, pathList[matMeshIndex]);
	}
	wstring hairShapeName = L"hair_Shape";

	wPath = textureFullPath + L"hair_01.jpg";
	pathList.clear();
	pathList.push_back(wPath);

	UTILITY_API->SetAvatarMeshTexture(hairShapeName, 0, pathList[0]);
}

string ReleaseTest_Nesting_GrainDir()
{
	string msg = "";

	msg += "[Start] ReleaseTest_Nesting_GrainDir\n";
	int patternCount = PATTERN_API->GetPatternCount();
	for (int i = 0; i < patternCount; ++i)
	{
		// GrainDirection //
		int beforeGrainDir = PATTERN_API->GetNestingPatternPieceGrainDirection(i);
		msg += "[" + to_string(i) + "] Before GrainDir : " + to_string(beforeGrainDir) + "\n";
		
		// 0:1-way, 1:2-way , 2:4-way
		// 012012012...
		PATTERN_API->SetNestingPatternPieceGrainDirection(i, i%3);

		int afterGrainDir = PATTERN_API->GetNestingPatternPieceGrainDirection(i);
		msg += "[" + to_string(i) + "] After GrainDir : " + to_string(afterGrainDir) + "\n";
	}

	msg += "\n";

	msg += "[End] ReleaseTest_Nesting_GrainDir\n\n";

	return msg;
}

string ReleaseTest_Nesting_FixedPos()
{
	string msg = "";

	msg += "[Start] ReleaseTest_Nesting_FixedPos\n";
	int patternCount = PATTERN_API->GetPatternCount();
	for (int i = 0; i < patternCount; ++i)
	{
		// FixedPos //
		pair<int, int> beforeFixedPos = PATTERN_API->GetNestingFixedPatternPiecePos(i);
		msg += "[" + to_string(i) + "] Before FixedPos : " + to_string(beforeFixedPos.first) + ", " + to_string(beforeFixedPos.second) + "\n";

		// 0:1-way, 1:2-way , 2:4-way
		// 012012012...
		PATTERN_API->SetNestingFixedPatternPiecePos(i, 200, (i+1)*(-200));

		pair<int, int> afterFixedPos = PATTERN_API->GetNestingFixedPatternPiecePos(i);
		msg += "[" + to_string(i) + "] After FixedPos : " + to_string(afterFixedPos.first) + ", " + to_string(afterFixedPos.second) + "\n";
	}

	msg += "\n";

	msg += "[End] ReleaseTest_Nesting_FixedPos\n\n";

	return msg;
}

string ReleaseTest_Nesting_BufferSpacing()
{
	string msg = "";

	msg += "[Start] ReleaseTest_Nesting_BufferSpacing\n";

	float bufferSpacing = UTILITY_API->GetNestingBufferSpacing();
	msg += "Before BufferSpacing : " + to_string(bufferSpacing) + "\n";

	if (bufferSpacing < 1.0f)
	{
		UTILITY_API->SetNestingBufferSpacing(3.0f);
	}
	else
	{
		UTILITY_API->SetNestingBufferSpacing(0.0f);
	}
	
	bufferSpacing = UTILITY_API->GetNestingBufferSpacing();
	msg += "After BufferSpacing : " + to_string(bufferSpacing) + "\n";
	
	msg += "\n";

	msg += "[End] ReleaseTest_Nesting_BufferSpacing\n\n";

	return msg;
}

string ReleaseTest_Nesting_TargetColorway()
{
	string msg = "";

	msg += "[Start] ReleaseTest_Nesting_TargetColorway\n";

	vector<int> targetColorways = UTILITY_API->GetNestingTargetColorway();
	msg += "Before TargetColorways Size : " + to_string(targetColorways.size()) + "\n";

	vector<int> newTarget;
	for (int i = 0; i < targetColorways.size(); ++i)
	{
		if (i % 2 == 0)
		{
			newTarget.push_back(i);
		}
	}
	
	msg += "targetColorways.size()" + to_string((int)(newTarget.size())) + "\n";

	UTILITY_API->SetNestingTargetColorway(newTarget);
	
	targetColorways = UTILITY_API->GetNestingTargetColorway();
	msg += "After TargetColorways Size : " + to_string(targetColorways.size()) + "\n";

	msg += "\n";

	msg += "[End] ReleaseTest_Nesting_TargetColorway\n\n";

	return msg;
}

string ReleaseTest_Nesting_Fabric_Width()
{
	string msg = "";

	msg += "[Start] ReleaseTest_Nesting_Fabric_Width\n";

	unsigned int fabricCount = FABRIC_API->GetFabricCount();
	for (unsigned int i = 0; i < fabricCount; ++i)
	{
		float fabricWidth_Before = FABRIC_API->GetFabricWidth(i);
		msg += "[" + to_string(i)+ "] Before fabricWidth : " + to_string(fabricWidth_Before) + "\n";

		FABRIC_API->SetFabricWidth(i, 1000.0f + (i * 10));
		
		float fabricWidth_After = FABRIC_API->GetFabricWidth(i);
		msg += "[" + to_string(i) + "] After fabricWidth : " + to_string(fabricWidth_After) + "\n";
	}

	msg += "\n";

	msg += "[End] ReleaseTest_Nesting_Fabric_Width\n\n";

	return msg;
}

string ReleaseTest_Nesting_Fabric_Length()
{
	string msg = "";

	msg += "[Start] ReleaseTest_Nesting_Fabric_Length\n";

	unsigned int fabricCount = FABRIC_API->GetFabricCount();
	for (unsigned int i = 0; i < fabricCount; ++i)
	{
		float fabricLength = FABRIC_API->GetFabricLength(i);
		msg += "[" + to_string(i) + "] FabricLength : " + to_string(fabricLength) + "\n";
	}

	msg += "\n";

	msg += "[End] ReleaseTest_Nesting_Fabric_Length\n\n";

	return msg;
}

void ImportFileByObjType_Sample()
{
	if (!IMPORT_API)
		return;

	string baseFolder = getHomePath() + "OBJFile/";
	string filePath = baseFolder + "test.FBX"; //must assign correct file path

	// avaliable options - import file type. 0 : Avatar, 1: Trim

	Marvelous::ImportExportOption options;
	options.ImportObjectType = 0;

	IMPORT_API->ImportFile(filePath, options);

}

void ImportFBX_Sample()
{
	if (!IMPORT_API)
		return;

	string baseFolder = getHomePath() + "OBJFile/";
	string filePath = baseFolder + "test.FBX"; //must assign correct file path

	Marvelous::ImportExportOption options;

	options.bCreateCamera = false;
	options.bCreateAnimation = false;
	options.bCreateCacheAnimation = false;
	options.bMoveGarment = false;
	options.bAddArrangementPoints = false;
	options.bAutoCreateFittingSuit = false;
	options.bAdd = false;
	options.ImportObjectType = 0;

	IMPORT_API->ImportFBX(filePath, options);

}

void ImportGLTF_Sample()
{
	if (!IMPORT_API)
		return;

	string baseFolder = getHomePath() + "OBJFile/";
	string filePath = baseFolder + "test.gltf"; //must assign correct file path

	Marvelous::ImportExportOption options;

	options.bAutoTranslate = false;
	options.bAddArrangementPoints = false;
	options.bAutoCreateFittingSuit = false;
	options.bAdd = false;

	options.scale = 1.0f;

	options.axisX = 0;
	options.axisY = 1;
	options.axisZ = 2;

	options.bInvertX = false;
	options.bInvertY = false;
	options.bInvertZ = false;

	options.ImportObjectType = 0;

	IMPORT_API->ImportGLTF(filePath, options);

}

void SetAnimationRecording_Test()
{
	if (!UTILITY_API)
		return;

	bool bRecording = true;
	UTILITY_API->SetAnimationRecording(bRecording);

	if (bRecording)
		UTILITY_API->DisplayMessageBox("Animation Recording Start.");
	else
		UTILITY_API->DisplayMessageBox("Animation Recording Stop.");

}

void SetCurrentAnimationFrame_Test()
{
	if (!UTILITY_API)
		return;

	double current = 1.0;
	UTILITY_API->SetCurrentAnimationFrame(current);

}

void GetCurrentAnimationFrame_Test()
{
	if (!UTILITY_API)
		return;

	double current = UTILITY_API->GetCurrentAnimationFrame();

	string msg = "Current Animation Frame : " + to_string(current);

	UTILITY_API->DisplayMessageBox(msg);
}

void SetStartAnimationFrame_Test()
{
	if (!UTILITY_API)
		return;

	double start = 1.0;
	UTILITY_API->SetStartAnimationFrame(start);

}

void GetStartAnimationFrame_Test()
{
	if (!UTILITY_API)
		return;

	double start = UTILITY_API->GetStartAnimationFrame();

	string msg = "Start Animation Frame : " + to_string(start);

	UTILITY_API->DisplayMessageBox(msg);
}

void SetEndAnimationFrame_Test()
{
	if (!UTILITY_API)
		return;

	double end = 1.0;
	UTILITY_API->SetEndAnimationFrame(end);

}

void GetEndAnimationFrame_Test()
{
	if (!UTILITY_API)
		return;

	double end = UTILITY_API->GetEndAnimationFrame();

	string msg = "End Animation Frame : " + to_string(end);

	UTILITY_API->DisplayMessageBox(msg);
}

void ImportSMP_Sample()
{
	if (!IMPORT_API)
		return;

	string baseFolder = getHomePath() + "SMP/";
	string filePath = baseFolder + "test.smp";

	IMPORT_API->ImportSMP(filePath);
}

void ImportSubstanceFileAsFaceType_Sample()
{
	if (!FABRIC_API || !UTILITY_API)
		return;

	string baseFolder = getHomePath() + "SBSAR/";
	string filePath = baseFolder + "test.sbsar";
	unsigned int fabricIndex = 0;
	string msg = "";

	bool bImport = FABRIC_API->ImportSubstanceFileAsFaceType(fabricIndex, filePath, "Side");

	if (bImport == false)
	{
		msg = "Import Substance File As FaceType is Fail.";
		UTILITY_API->DisplayMessageBox(msg);
	}
}

void ImportTrim_Test()
{
	if (!IMPORT_API)
		return;

	const string baseFolder = getHomePath() + "Trim/";
	const string filePath = baseFolder + "test.trm";
	const bool bTranslateToOrigin = false;

	IMPORT_API->ImportTrim(filePath, bTranslateToOrigin);

	const string info_msg = "Complete Import Trim: " + filePath;
	UTILITY_API->DisplayMessageBox(info_msg);
}

void ImportAsGraphic_Sample() {

	if (!IMPORT_API)
		return;

	string baseFolder = getHomePath() + "Texture/";
	string filePath = baseFolder + "test.png";

	IMPORT_API->ImportAsGraphic(filePath);
}

void ExportAVT_Sample()
{
	if (!EXPORT_API || !UTILITY_API)
		return;

	string baseFolder = getHomePath() + "export_avt/";
	string exportedFilePath = EXPORT_API->ExportAVT(baseFolder + "test.avt");

	if (UTILITY_API)
		UTILITY_API->DisplayMessageBox(exportedFilePath);
}

void SetTextureMapping_Sample() {
	if (!FABRIC_API) return;

	const unsigned int fabricIndex = 0;
	const int		   mappingType = 0;

	FABRIC_API->SetTextureMapping(fabricIndex, mappingType);
}

void SetSubstancePreset_Sample() {
	if (!FABRIC_API) return;

	const unsigned int fabricIndex	= 0;
	const int		   materialFace = 0;
	const int		   presetIndex	= 0;

	FABRIC_API->SetSubstancePreset(fabricIndex, materialFace, presetIndex);
}

void SetSubstanceResolution_Sample() {
	if (!FABRIC_API) return;

	const unsigned int fabricIndex	   = 0;
	const int		   materialFace	   = 0;
	const int		   resolutionIndex = 0;

	FABRIC_API->SetSubstanceResolution(fabricIndex, materialFace, resolutionIndex);
}

void PatternAnnotation_Test()
{
	if (!PATTERN_API)
		return;

	vector<tuple<float, float, int>> createPatternPoints = {
		make_tuple(0.0f, -300.0f, 0)
		, make_tuple(0.0f, -200.0f, 0)
		, make_tuple(100.0f, -200.0f, 0)
		, make_tuple(100.0f, -300.0f, 0)
	};
	PATTERN_API->CreatePatternWithPoints(createPatternPoints);
	
	PATTERN_API->AddPatternAnnotation(0, 0, 0, "Test");
	string msg = "Annotation : " + std::get<0>(PATTERN_API->GetPatternAnnotation(0).back());
	UTILITY_API->DisplayMessageBox(msg);

	PATTERN_API->EditPatternAnnotation(0, 0, 0, 0, "EditTest");
	msg = "Annotation : " + std::get<0>(PATTERN_API->GetPatternAnnotation(0).back());
	UTILITY_API->DisplayMessageBox(msg);
}

void GetLinkedPatternIndex_Test()
{
	if (!PATTERN_API)
		return;

	vector<tuple<float, float, int>> createPatternPoints = {
		make_tuple(0.0f, -300.0f, 0)
		, make_tuple(0.0f, -200.0f, 0)
		, make_tuple(100.0f, -200.0f, 0)
		, make_tuple(100.0f, -300.0f, 0)
	};
	PATTERN_API->CreatePatternWithPoints(createPatternPoints);

	auto indexlist = PATTERN_API->GetLinkedPatternIndex(0);

	string msg = "linked Pattern Count : " + std::to_string(indexlist.size());
	UTILITY_API->DisplayMessageBox(msg);
}

void StatusStressMap_Test()
{
	if (!UTILITY_API)
		return;

	bool bOn = UTILITY_API->GetStressMapStatus();
	string statusMsg = bOn ? "On" : "Off";
	string msg = "Current Rendered Status of Stress Map : " + statusMsg;
	UTILITY_API->DisplayMessageBox(msg);

	UTILITY_API->SetStressMapStatus(!bOn);

	bOn = UTILITY_API->GetStressMapStatus();
	statusMsg = bOn ? "On" : "Off";
	msg = "Changed Rendered Status of Stress Map : " + statusMsg;
	UTILITY_API->DisplayMessageBox(msg);
}

void StatusStrainMap_Test()
{
	if (!UTILITY_API)
		return;

	bool bOn = UTILITY_API->GetStrainMapStatus();
	string statusMsg = bOn ? "On" : "Off";
	string msg = "Current Rendered Status of Strain Map : " + statusMsg;
	UTILITY_API->DisplayMessageBox(msg);

	UTILITY_API->SetStrainMapStatus(!bOn);

	bOn = UTILITY_API->GetStrainMapStatus();
	statusMsg = bOn ? "On" : "Off";
	msg = "Changed Rendered Status of Strain Map : " + statusMsg;
	UTILITY_API->DisplayMessageBox(msg);
}

void RefreshPlugIns_Sample()
{
	if (!UTILITY_API)
		return;
	
	UTILITY_API->RefreshPlugIns();

	string msg = "Refresh plugins";

	UTILITY_API->DisplayMessageBox(msg);
}

void SetCamViewPoint_Test()
{
	if (!UTILITY_API)
		return;

	int  camViewPointIndex = 0;

	UTILITY_API->SetCamViewPoint(camViewPointIndex);

}

void SetUseSameMaterialAsFront_Sample() {
	if (!FABRIC_API) return;

	const unsigned int fabricIndex = 0;
	const int		   materialFace = 1;
	const bool		   useSameMaterialAsFront = false;

	FABRIC_API->SetUseSameMaterialAsFront(fabricIndex, materialFace, useSameMaterialAsFront);
}

void SetUseSameColorAsFront_Sample() {
	if (!FABRIC_API) return;

	const unsigned int fabricIndex = 0;
	const int		   materialFace = 1;
	const bool		   useSameColorAsFront = false;

	FABRIC_API->SetUseSameColorAsFront(fabricIndex, materialFace, useSameColorAsFront);
}

void CreateModularCategory_Test()
{
	if (!UTILITY_API)
		return;

	std::wstring title = L"new_block";
	std::wstring path =  L"C:/Modular";

	UTILITY_API->CreateModularCategory(title, path);
}

void DeleteModularCategory_Test()
{
	if (!UTILITY_API)
		return;
	std::wstring title = L"test_title";
	UTILITY_API->DeleteModularCategory(title);
}

void SetSchematicSilhouetteLineWidth_Test()
{
	if (!UTILITY_API)
		return;

	int  lineWidth = 1;

	UTILITY_API->SetSchematicSilhouetteLineWidth(lineWidth);

}

void SetSchematicSeamLineWidth_Test()
{
	if (!UTILITY_API)
		return;

	int lineWidth = 1;

	UTILITY_API->SetSchematicSeamLineWidth(lineWidth);
}

void SetSchematicInternalLineWidth_Test()
{
	if (!UTILITY_API)
		return;

	int lineWidth = 1;

	UTILITY_API->SetSchematicInternalLineWidth(lineWidth);
}

void SetSchematicTopstitchLineScalePercent_Test()
{
	if (!UTILITY_API)
		return;

	int scalePercent = 100;

	UTILITY_API->SetSchematicTopstitchLineScalePercent(scalePercent);
}

void SetSchematicBrightness_Test()
{
	if (!UTILITY_API)
		return;

	int brightness = 1;

	UTILITY_API->SetSchematicBrightness(brightness);
}

void SetShowSchematicSilhouetteLine_Test()
{
	if (!UTILITY_API)
		return;

	bool bOn = true;

	UTILITY_API->SetShowSchematicSilhouetteLine(bOn);
}

void SetShowSchematicSeamLine_Test()
{
	if (!UTILITY_API)
		return;

	bool bOn = true;

	UTILITY_API->SetShowSchematicSeamLine(bOn);
}

void SetShowSchematicInternalLine_Test()
{
	if (!UTILITY_API)
		return;

	bool bOn = true;

	UTILITY_API->SetShowSchematicInternalLine(bOn);
}

void SetShowSchematicTopstitchLine_Test()
{
	if (!UTILITY_API)
		return;

	bool bOn = true;

	UTILITY_API->SetShowSchematicTopstitchLine(bOn);
}

void SetSchematicClothRenderType_Test()
{
	if (!UTILITY_API)
		return;

	bool bTexture = true;

	UTILITY_API->SetSchematicClothRenderType(bTexture);
}

void SetStyleLineColor_Test()
{
	if (!UTILITY_API)
		return;

	int r = 100;
	int g = 100;
	int b = 100;

	UTILITY_API->SetStyleLineColor(r, g, b);
}

void SetSchematicClothColor_Test()
{
	if (!UTILITY_API)
		return;

	int r = 100;
	int g = 100;
	int b = 100;

	UTILITY_API->SetSchematicClothColor(r, g, b);
}

void GetTopstitchStyleModel_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	string msg = "";

	int defaultTopstitchStyleIndex = 0;
	int topstitchModelType = PATTERN_API->GetTopstitchStyleModelType(defaultTopstitchStyleIndex);

	if (topstitchModelType >= 0)
	{
		if (topstitchModelType == 0)
			msg = "The Default Topstitch Style is OBJ type.";
		else
			msg = "The Default Topstitch Style is Texture type.";
	}
	else
		msg = "Topstitch Style List is Empty.";

	UTILITY_API->DisplayMessageBox(msg);
}

void SetTopstitchStyleModel_Test()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	string msg = "";

	int defaultTopstitchStyleIndex = 0;
	int topstitchModelType = PATTERN_API->GetTopstitchStyleModelType(defaultTopstitchStyleIndex);

	if (topstitchModelType >= 0)
	{
		int changedModelType = 0;
		if (topstitchModelType == 0)
			changedModelType = 1;
		else
			changedModelType = 0;

		bool bResult = PATTERN_API->SetTopstitchStyleModelType(defaultTopstitchStyleIndex, changedModelType);
		if (bResult == true)
		{
			msg = "Success to Change Topstitch Model Type.\n";

			if (changedModelType == 0)
				msg.append("The Changed Topstitch Style is OBJ type.");
			else
				msg.append("The Changed Topstitch Style is Texture type.");
		}
		else
			msg = "Fail to Change Topstitch Model Type.";
	}
	else
		msg = "Topstitch Style List is Empty";

	UTILITY_API->DisplayMessageBox(msg);
}

void CreateZfabFromTextures_Test()
{
	if (!FABRIC_API || !UTILITY_API)
		return;

	string msg = "";

	string baseFolder = getHomePath() + "fabric/";
	
	string zFabFilePath = baseFolder + "test.zfab";

	string BaseTextureFilePath = baseFolder + "BaseTexture.jpg";
	
	string NormalTexturePath = baseFolder + "NormalTexture.jpg";
	
	string DisplacementTexturePath = baseFolder + "DisplacementTexture.jpg";
	
	string OpacityTextureePath = baseFolder + "OpacityTexture.jpg";

	string RoughnessTextureePath = baseFolder + "RoughnessTexture.jpg";

	string MetalnessTextureePath = baseFolder + "MetalnessTexture.jpg";

	bool bResult = FABRIC_API->CreateZfabFromTextures(zFabFilePath, BaseTextureFilePath, NormalTexturePath, DisplacementTexturePath, OpacityTextureePath, RoughnessTextureePath, MetalnessTextureePath);

	if (bResult == true)
	{
		msg = "Success to Create Zfab From Textures.\n";
	}
	else
	{
		msg = "Fail to Create Zfab From Textures_Test.\n";
	}

	UTILITY_API->DisplayMessageBox(msg);

}

void CombineZfab_Test()
{
	if (!FABRIC_API)
		return;

	string baseFolder = getHomePath() + "fabric/";

	string zFabFilePath = baseFolder + "test.zfab";

	string baseZfabPath = baseFolder + "physicalProperty.zfab";
	string targetZfabPath = baseFolder + "image.zfab";

	FABRIC_API->CombineZfab(zFabFilePath, baseZfabPath, targetZfabPath);
}

void BakeUVTexture_Test()
{
	if (!UTILITY_API)
		return;

	// the other options are given as default. please refer to ImportExportOption class in ExportAPI.h
	Marvelous::ImportExportOption options;
	options.unifiedTextureSize = 2048;
	options.unifiedTextureFillSeamSize = 10;
	options.bUseInifinteSeams = false;
	options.bUnifiedDiffuseMap = true;
	options.bUnifiedMetalnessMap = true;
	options.bUnifiedNormalMap = true;
	options.bUnifiedRoughnessMap = true;
	options.bUnifiedOpacityMap = true;
	options.bUnifiedDisplacementMap = true;
	bool bAlltile = true;

	string path = getHomePath() + "UV_Texture/test.png";
	vector<string> savedFilePathList = UTILITY_API->BakeUVTexture(path, options, bAlltile);

	string resultPaths = "Total Baked Texture Image Paths :\n";
	for (const auto& savedPath : savedFilePathList)
		resultPaths.append(savedPath + "\n");
	
	UTILITY_API->DisplayMessageBox(resultPaths);
}

void UVPacking_Test()
{
	if (!UTILITY_API)
		return;

	bool bPackAllPatterns = true;
	bool bFixScaleRatio = true;
	bool bAdvancedSearch = true;
	float padding = 0.001f;
	int fidelity = 3;
	vector<int> rotationOptions = { 0, 90, 180, 270 };

	bool bResult = UTILITY_API->UVPacking(bPackAllPatterns, bFixScaleRatio, bAdvancedSearch, padding, fidelity, rotationOptions);

	if (bResult == true)
		UTILITY_API->DisplayMessageBox("UV Packing is finished.");
	else
		UTILITY_API->DisplayMessageBox("UV Packing is failed.");
}
void GetRoughnessInFabric_Test()
{
	if (!FABRIC_API || !UTILITY_API)
		return;

	string msg = "";
	int defaultFabricIndex = 0;
	int defaultMaterialFace = 0;
	int roughnessType = FABRIC_API->GetRoughnessType(defaultFabricIndex, 0);

	if (roughnessType == 0)
		msg += "Roughness is intensity Type\n";
	else if (roughnessType == 1)
		msg += "Roughness is map Type\n";
	else
		msg += "Error!\n";

	int fIValue = FABRIC_API->GetRoughnessValueIntensity(0, 0);
	int sIValue = FABRIC_API->GetRoughnessValueIntensity(0, 1);
	int bIValue = FABRIC_API->GetRoughnessValueIntensity(0, 2);

	msg += ("Internsity value - front : " + std::to_string(fIValue) + ", side : " + std::to_string(sIValue) + ", back : " + std::to_string(bIValue) + "\n");

	int fMValue = FABRIC_API->GetRoughnessValueMapIntensity(0, 0);
	int sMValue = FABRIC_API->GetRoughnessValueMapIntensity(0, 1);
	int bMValue = FABRIC_API->GetRoughnessValueMapIntensity(0, 2);

	msg += ("Map internsity value - front : " + std::to_string(fMValue) + ", side : " + std::to_string(sMValue) + ", back : " + std::to_string(bMValue) + +"\n");
	
	bool bFInverted = FABRIC_API->IsRoughnessValueMapInvert(0, 0);
	bool bSInverted = FABRIC_API->IsRoughnessValueMapInvert(0, 1);
	bool bBInverted = FABRIC_API->IsRoughnessValueMapInvert(0, 2);

	msg += ("whether roughness map is inverted - front : " + std::to_string(bFInverted) + ", side : " + std::to_string(bSInverted) + ", back : " + std::to_string(bBInverted) + +"\n");

	UTILITY_API->DisplayMessageBox(msg);
}

void SetRoughnessInFabric_Test()
{
	if (!FABRIC_API || !UTILITY_API)
		return;

	string msg = "";

	int defaultFabricIndex = 0;

	FABRIC_API->SetRoughnessType(0, 0, 1);
	FABRIC_API->SetRoughnessValueMapIntensity(0, 0, 70);
	FABRIC_API->SetRoughnessValueMapInvert(0, 0, true);
}

void ExportTrim_Test()
{
	if (!EXPORT_API || !UTILITY_API)
		return;

	unsigned int trimIndex = 0; // default trim, the 1st trim on the object browser in CLO S/W

	string baseFolder = getHomePath() + "trim/";
	string trimFilePath = baseFolder + "test.trm";

	string exportPath = EXPORT_API->ExportTrim(trimFilePath, trimIndex);

	string msg = "Export Trim Complete: " + exportPath;

	UTILITY_API->DisplayMessageBox(msg);
}

void SetTrimWeight_Test()
{
	if (!UTILITY_API)
		return;

	unsigned int trimIndex = 0; // default trim, the 1st trim on the object browser in CLO S/W

	float mass = 1.0f;

	UTILITY_API->SetTrimWeight(trimIndex, mass);
}

void GetObjectBrowserMaterialUsed()
{
	if (!PATTERN_API || !UTILITY_API)
		return;

	string data = PATTERN_API->ExportObjectBrowserMaterialsList();
}

void ExportStdViewImage_Sample()
{
	if (!EXPORT_API)
		return;

	string savePath = getHomePath() + "SnapShot/" + "test.png";

	int imageViewIndex = 0;
	int selectedColorwayIndex = 0;
	int width = 2500;
	int height = 2500;

	EXPORT_API->ExportStdViewImage(imageViewIndex, savePath, selectedColorwayIndex, width, height);
}

void ExportStdViewImageForAllColorways_Sample()
{
	if (!EXPORT_API)
		return;

	string savePath = getHomePath() + "SnapShot/" + "test.png";

	int imageViewIndex = 0;
	int width = 2500;
	int height = 2500;

	EXPORT_API->ExportStdViewImageForAllColorways(imageViewIndex, savePath, width, height);
}

void ExportCustomViewImage_Sample()
{
	if (!EXPORT_API)
		return;

	string zcmrFilePath = getHomePath() + "ZCMR/" + "test.zcmr";
	string savePath = getHomePath() + "SnapShot/" + "test.png";

	int selectedColorwayIndex = 0;
	int width = 2500;
	int height = 2500;

	EXPORT_API->ExportCustomViewImage(zcmrFilePath, savePath, selectedColorwayIndex, width, height);
}

void ExportCustomViewImageForAllColorways_Sample()
{
	if (!EXPORT_API)
		return;

	string zcmrFilePath = getHomePath() + "ZCMR/" + "test.zcmr";
	string savePath = getHomePath() + "SnapShot/" + "test.png";

	int width = 2500;
	int height = 2500;

	EXPORT_API->ExportCustomViewImageForAllColorways(zcmrFilePath, savePath, width, height);
}

void ExportMultiViewImages_Sample()
{
	if (!EXPORT_API)
		return;

	string mvsFilePath = getHomePath() + "MVS/" + "test.mvs";
	string savePath = getHomePath() + "SnapShot/" + "test.png";

	int selectedColorwayIndex = 0;
	int width = 2500;
	int height = 2500;

	EXPORT_API->ExportMultiViewImages(mvsFilePath, savePath, selectedColorwayIndex, width, height);
}

void ExportMultiViewImagesForAllColorways_Sample()
{
	if (!EXPORT_API)
		return;

	string mvsFilePath = getHomePath() + "MVS/" + "test.mvs";
	string savePath = getHomePath() + "SnapShot/" + "test.png";

	int width = 2500;
	int height = 2500;

	EXPORT_API->ExportMultiViewImagesForAllColorways(mvsFilePath, savePath, width, height);
}

void GetPinList()
{
	if (!PATTERN_API)
		return;

	auto data = PATTERN_API->GetPinList();
}

void RemovePinByIndex(int _index)
{
	if (!PATTERN_API)
		return;

	PATTERN_API->RemovePinByIndex(_index);
}
void ChangeGradingSize()
{
	//way 1. use grading name
	// If your goal is simply to change the size, we recommend using a function with 'valid'.
	auto gradingSizeGroupList = PATTERN_API->GetValidGradingSizeGroupInformation();

	if(gradingSizeGroupList.empty())
		return;

	//Get a list of the desired group sizes.
	auto gradingSizeList = PATTERN_API->GetGradingSizeListFromRuleTable(gradingSizeGroupList[0]);

	if(gradingSizeList.empty())
		return;

	//Now let's change the grading size.
	PATTERN_API->ChangeGradingSizeInformation(gradingSizeGroupList[0], gradingSizeList[1]);

	//way 2. use index
	auto gradingSizeGroupCount = PATTERN_API->GetValidGradingSizeGroupCount();

	if(!gradingSizeGroupCount)
		return;
	
	for(int i=0; i<gradingSizeGroupCount; ++i)
	{
		auto gradingSizeList =  PATTERN_API->GetGradingSizeListFromRuleTable(i);
		for (int j=0; j<gradingSizeList.size(); ++j) {
			PATTERN_API->ChangeGradingSizeInformation(i,j);
		}
	}
}

void ConvertZblcToZmod_Test()
{
	if (!EXPORT_API)
		return;
	 std::vector<std::wstring> zblcPathList = { 
	 	L"C:\\ZPac\\S-GLX7424S23_RaglanCN_Leg1.zblc",
	 	L"C:\\ZPac\\S-GLX7424S23_RaglanCN_Leg2.zblc",
	 	L"C:\\ZPac\\S-GLX7424S23_RaglanCN_Leg3.zblc",
	 };

	
	std::wstring savePath = L"/Users/moon/Documents/New Blocks";
	std::wstring category = L"API_TEST";
	std::wstring style = L"Hood";

	auto failedPathList = EXPORT_API->ConvertZblcToZmod(zblcPathList, savePath, category, style);

//	#include <iostream>
// 	std::cout << "Convert Failed Path List :" << std::endl;
// 
// 	for (const auto& path : failedPathList)
// 	{
// 		std::cout << "> " << path.c_str() << std::endl;
// 	}
}

void Refresh3DWindow_Test()
{
	if (!UTILITY_API)
		return;
	
	UTILITY_API->Refresh3DWindow();
}

void SetColorwayColorItem_Test()
{
	if (!UTILITY_API)
		return;

	int colorwayIndex = 0;
	int colorItemIndex = 0;
	string plmId = "0x00";
	string name = "new color";
	Marvelous::CloApiRgb rgb;
	rgb.R = 255;
	rgb.G = 255;
	
	UTILITY_API->SetColorwayColorItem(colorwayIndex, colorItemIndex, plmId, name, rgb);
}

void GetColorwayColorItemRGB_Test()
{
	if (!UTILITY_API)
		return;

	int colorwayIndex = 0;
	int colorItemIndex = 0;

	Marvelous::CloApiRgb rgb = UTILITY_API->GetColorwayColorItemRGB(colorwayIndex, colorItemIndex);
}

void GetColorwayColorItemPlmId_Test()
{
	if (!UTILITY_API)
		return;

	int colorwayIndex = 0;
	int colorItemIndex = 0;

	string plmId = UTILITY_API->GetColorwayColorItemPlmId(colorwayIndex, colorItemIndex);
}

void GetColorwayColorItemName_Test()
{
	if (!UTILITY_API)
		return;

	int colorwayIndex = 0;
	int colorItemIndex = 0;

	string name = UTILITY_API->GetColorwayColorItemName(colorwayIndex, colorItemIndex);
}

void RemovePlugInFromList()
{
	if (!UTILITY_API)
		return;

	int pluginListIndex = 0;

	UTILITY_API->RemovePlugInFromList(pluginListIndex);
}

void AddPlugInFromFile()
{
	if (!UTILITY_API)
		return;

	string baseFolder = getHomePath() + "DLL/";
	string filePath = baseFolder + "plugin.dll";

	UTILITY_API->AddPlugInFromFile(filePath);
}

void UsePlugInFromList()
{
	if (!UTILITY_API)
		return;

	int  pluginListIndex = 0;

	UTILITY_API->UsePlugInFromList(pluginListIndex);
}

void TerminatePlugInFromList()
{
	if (!UTILITY_API)
		return;

	int  pluginListIndex = 0;

	UTILITY_API->TerminatePlugInFromList(pluginListIndex);
}

void ChangeDisplacementMapValue(){
    if(!FABRIC_API){
        return;
    }

    FABRIC_API->SetPBRMaterialDisplacementMap(0, "test.png");
    FABRIC_API->SetPBRMaterialDisplacementMapValue(0, 5, 4, 3, 2, true);
    FABRIC_API->GetPBRMaterialDisplacementMapValue(0);
}

void AddSeamlineStitchToPattern_Test(){

	if (!PATTERN_API) {
		return;
	}
	/*
		Before you run this function, you must have the following set up in your scene
		- At least one Pattern must exist in the scene.
		- At least 1 Sewing must exist in the scene.
	*/
	int patternIndex = 0;
	int lineIndex = 0;
	float startRatio = 0.0f;
	float endRatio = 1.0f;
	int topStitchStyleIndex = 0;

	std::vector<unsigned int> seamlineGroupIndexList = PATTERN_API->GetSeamlinePairGroupListInPattern(patternIndex);

	if (seamlineGroupIndexList.empty())
		return;

	PATTERN_API->AddSeamlineTopstitch(seamlineGroupIndexList[0], startRatio, endRatio, topStitchStyleIndex);
}

void GetSeamlinePairGroupCount_Test()
{
	if (!PATTERN_API)
		return;

	int count = PATTERN_API->GetSeamlinePairGroupCount();
	string msg = "SeamlinePairGroup Count : " + to_string(count);
	UTILITY_API->DisplayMessageBox(msg);
}

void GetSeamlinePairGroupName_Test()
{
	if (!PATTERN_API)
		return;

	std::string name = PATTERN_API->GetSeamlinePairGroupName(0);
	string msg = "SeamlinePairGroup Name : " + name;
	UTILITY_API->DisplayMessageBox(msg);
}

void GetSeamlinePairGroupIndexFromName_Test()
{
	if (!PATTERN_API)
		return;

	int index = PATTERN_API->GetSeamlinePairGroupIndexFromName("test");
	string msg = "SeamlinePairGroup Index : " + to_string(index);
	UTILITY_API->DisplayMessageBox(msg);
}

void GetAllStitchProperty_Test()
{
	if (!PATTERN_API)
		return;

	string jsonStr = PATTERN_API->GetAllStitchProperty();

	UTILITY_API->DisplayMessageBox(jsonStr);
}

void AddSeamlinePairGroup_Test()
{
	if (!PATTERN_API)
		return;
/*
	Before you run this function, you must have the following set up in your scene
	- At least two Pattern must exist in the scene.
	- At least two innershape must exist in the scene.
*/
	int patternAIndex = 0;
	int patternBIndex = 1;
	int lineIndex = 0;
	int childIndex = 0;

	//pattern to pattern sewing
	PATTERN_API->AddSeamlinePairGroup(patternAIndex, lineIndex, patternBIndex, lineIndex, true, false);

	//pattern to innershape
	PATTERN_API->AddSeamlinePairGroup(patternAIndex, lineIndex, patternBIndex, childIndex, lineIndex, true, true);

	//innershape to innershape
	PATTERN_API->AddSeamlinePairGroup(patternAIndex, childIndex, lineIndex, patternBIndex, childIndex, lineIndex, false, true);
}

void GetGradingPairedAvatar()
{
	if (!PATTERN_API)
		return;

	PATTERN_API->GetGradingPairedAvatar(1);
}

void ExportPatternJSON()
{
	if (!PATTERN_API)
		return;

	string baseFolder = getHomePath() + "Pattern/";
	string filePath = baseFolder + "pattern.json";

	PATTERN_API->ExportPatternJSON(filePath);
}

void ImportPatternJSON(string _path)
{
	if (!PATTERN_API)
		return;

	string baseFolder = getHomePath() + "Pattern/";
	string filePath = baseFolder + "pattern.json";

	PATTERN_API->ImportPatternJSON(filePath);
}

void GetReflectionRoughness_Test() {
	if (!FABRIC_API || !UTILITY_API) return;

	float reflectionRoughness = FABRIC_API->GetReflectionRoughness(1, 0);
	string message = "reflectionRoughness value: " + to_string(reflectionRoughness);
	UTILITY_API->DisplayMessageBox(message);
}

void SetReflectionRoughness_Test() {
	if (!FABRIC_API || !UTILITY_API) return;

	FABRIC_API->SetReflectionIntensity(1, 0, 1.0f);
}

void GetReflectionIntensity_Test() {
	if (!FABRIC_API || !UTILITY_API) return;

	float reflectionIntensity = FABRIC_API->GetReflectionIntensity(1, 0);
	string message = "reflectionIntensity value: " + to_string(reflectionIntensity);
	UTILITY_API->DisplayMessageBox(message);
}

void SetReflectionIntensity_Test() {
	if (!FABRIC_API || !UTILITY_API) return;

	FABRIC_API->SetReflectionIntensity(1, 0, 1.0f);
}


void GetMetalness_Test() {
	if (!FABRIC_API || !UTILITY_API) return;

	float metalness = FABRIC_API->GetMetalness(1, 0);
	string message = "metalness value: " + to_string(metalness);
	UTILITY_API->DisplayMessageBox(message);
}

void SetMetalness_Test() {
	if (!FABRIC_API || !UTILITY_API) return;

	FABRIC_API->SetMetalness(1, 0, 1.0f);
}

void GetNormalMapIntensity_Test() {
	if (!FABRIC_API || !UTILITY_API) return;

	float normalMapIntensity = FABRIC_API->GetNormalMapIntensity(1, 0);
	string message = "normalMapIntensity value: " + to_string(normalMapIntensity);
	UTILITY_API->DisplayMessageBox(message);
}

void SetNormalMapIntensity_Test() {
	if (!FABRIC_API || !UTILITY_API) return;

	FABRIC_API->SetNormalMapIntensity(1, 0, 100.0f);
}

void GetMaterialType_Test() {
	if (!FABRIC_API || !UTILITY_API) return;

	int materialType = FABRIC_API->GetMaterialType(1, 0);
	string message = "materialType: " + to_string(materialType);
	UTILITY_API->DisplayMessageBox(message);
}

void SetMaterialType_Test() {
	if (!FABRIC_API || !UTILITY_API) return;

	int materialType = 1;
	FABRIC_API->SetMaterialType(1, 0, materialType);
}

void GetOpacityIntensity_Test() {
	if (!FABRIC_API || !UTILITY_API) return;

	float opacityIntensity = FABRIC_API->GetOpacityIntensity(1, 0);
	string message = "opacityIntensity value: " + to_string(opacityIntensity);
	UTILITY_API->DisplayMessageBox(message);
}

void SetOpacityIntensity_Test() {
	if (!FABRIC_API || !UTILITY_API) return;

	FABRIC_API->SetOpacityIntensity(1, 0, 100.0f);
}

void GetTotalGraphicItemQuantity_Test() {
	if (!UTILITY_API)
		return;

	int quantity = UTILITY_API->GetTotalGraphicItemQuantity();
}

void GetGraphicStyleCount_Test() {
	if (!UTILITY_API)
		return;

	int nStyle = UTILITY_API->GetGraphicStyleCount();
}

void GetGraphicStyleName_Test() {
	if (!UTILITY_API)
		return;

	int index = 0;
	std::string name = UTILITY_API->GetGraphicStyleName(index);
}

void GetGraphicStyleDimensions_Test() {
	if (!UTILITY_API)
		return;

	int index = 0;
	Marvelous::CloApiGraphicDimensions dimensions = UTILITY_API->GetGraphicStyleDimensions(index);
}

void SetGraphicStyleName_Test() {
	if (!UTILITY_API)
		return;

	int index = 0;
	UTILITY_API->SetGraphicStyleName(index, "test");
	auto name = UTILITY_API->GetGraphicStyleName(0);
	//UTILITY_API->DisplayMessageBox((name == "test")?"it works":"something wrong");
}

void SetGraphicStyleDimensions_Test() {
	if (!UTILITY_API)
		return;

	int index = 0;
	float width = 350.5;
	float height = 311.3;
	UTILITY_API->SetGraphicStyleDimensions(index, width, height);
	Marvelous::CloApiGraphicDimensions dimensions = UTILITY_API->GetGraphicStyleDimensions(index);
	//if (dimensions.width - width < FLT_EPSILON &&
	//	dimensions.height - height < FLT_EPSILON) {
	//	UTILITY_API->DisplayMessageBox("it works");
	//}
	//else {
	//	UTILITY_API->DisplayMessageBox("something wrong");
	//}
}

void SetGraphicStyleWidth_Test() {
	if (!UTILITY_API)
		return;

	int index = 0;
	float width = 350.5;
	UTILITY_API->SetGraphicStyleWidth(index, width, true);
	Marvelous::CloApiGraphicDimensions dimensions = UTILITY_API->GetGraphicStyleDimensions(index);
	//if (dimensions.width - width < FLT_EPSILON) {
	//	UTILITY_API->DisplayMessageBox("it works");
	//}
	//else {
	//	UTILITY_API->DisplayMessageBox("something wrong");
	//}
}

void SetGraphicStyleHeight_Test() {
	if (!UTILITY_API)
		return;

	int index = 0;
	float height = 311.3;
	UTILITY_API->SetGraphicStyleHeight(index, height, true);
	Marvelous::CloApiGraphicDimensions dimensions = UTILITY_API->GetGraphicStyleDimensions(index);
	//if (dimensions.height - height < FLT_EPSILON) {
	//	UTILITY_API->DisplayMessageBox("it works");
	//}
	//else {
	//	UTILITY_API->DisplayMessageBox("something wrong");
	//}
}

void GetBaseTextureMapImageFilePath_Sample()
{
	if (!FABRIC_API)
		return;

	if (!UTILITY_API)
		return;

	string imageFilePath = FABRIC_API->GetBaseTextureMapImageFilePath();
	UTILITY_API->DisplayMessageBox(imageFilePath);
}

void GetNormalMapImageFilePath_Sample()
{
	if (!FABRIC_API)
		return;

	if (!UTILITY_API)
		return;

	string imageFilePath = FABRIC_API->GetNormalMapImageFilePath();
	UTILITY_API->DisplayMessageBox(imageFilePath);
}

void GetDisplacementMapImageFilePath_Sample()
{
	if (!FABRIC_API)
		return;

	if (!UTILITY_API)
		return;

	string imageFilePath = FABRIC_API->GetDisplacementMapImageFilePath();
	UTILITY_API->DisplayMessageBox(imageFilePath);
}

void GetOpacityMapImageFilePath_Sample()
{
	if (!FABRIC_API)
		return;

	if (!UTILITY_API)
		return;

	string imageFilePath = FABRIC_API->GetOpacityMapImageFilePath();
	UTILITY_API->DisplayMessageBox(imageFilePath);
}

void GetRoughnessMapImageFilePath_Sample()
{
	if (!FABRIC_API)
		return;

	if (!UTILITY_API)
		return;

	string imageFilePath = FABRIC_API->GetRoughnessMapImageFilePath();
	UTILITY_API->DisplayMessageBox(imageFilePath);
}

void GetMetalnessMapImageFilePath_Sample()
{
	if (!FABRIC_API)
		return;

	if (!UTILITY_API)
		return;

	string imageFilePath = FABRIC_API->GetMetalnessMapImageFilePath();
	UTILITY_API->DisplayMessageBox(imageFilePath);
}

void SetBaseTextureMapImageGivenFilePath_Sample()
{
	if (!FABRIC_API)
		return;

	string baseFolder = getHomePath();
	string sampleFilePath = baseFolder +"test/Sample/crab.png";

	FABRIC_API->SetBaseTextureMapImageGivenFilePath(sampleFilePath);
}

void SetNormalMapImageGivenFilePath_Sample()
{
	if (!FABRIC_API)
		return;

	string baseFolder = getHomePath();
	string sampleFilePath = baseFolder + "test/Sample/crab.png";

	FABRIC_API->SetNormalMapImageGivenFilePath(sampleFilePath);
}

void SetDisplacementMapImageGivenFilePath_Sample()
{
	if (!FABRIC_API)
		return;

	string baseFolder = getHomePath();
	string sampleFilePath = baseFolder + "test/Sample/crab.png";

	FABRIC_API->SetDisplacementMapImageGivenFilePath(sampleFilePath);
}

void SetOpacityMapImageGivenFilePath_Sample()
{
	if (!FABRIC_API)
		return;

	string baseFolder = getHomePath();
	string sampleFilePath = baseFolder + "test/Sample/crab.png";

	FABRIC_API->SetOpacityMapImageGivenFilePath(sampleFilePath);
}

void SetRoughnessMapImageGivenFilePath_Sample()
{
	if (!FABRIC_API)
		return;

	string baseFolder = getHomePath();
	string sampleFilePath = baseFolder + "test/Sample/crab.png";

	FABRIC_API->SetRoughnessMapImageGivenFilePath(sampleFilePath);
}

void SetMetalnessMapImageGivenFilePath_Sample()
{
	if (!FABRIC_API)
		return;

	string baseFolder = getHomePath();
	string sampleFilePath = baseFolder + "test/Sample/crab.png";

	FABRIC_API->SetMetalnessMapImageGivenFilePath(sampleFilePath);
}

void ExportBOM_Sample()
{
	if (!EXPORT_API)
		return;

	string baseFolder = getHomePath();
	string sampleFilePath = baseFolder + "test/Sample";

	EXPORT_API->ExportBOM(sampleFilePath);
}

void ReplaceFabric_Sample()
{
	if (FABRIC_API == nullptr)
		return;

	string baseFolder = getHomePath() + "fabric/";
	string zFabFilePath = baseFolder + "test.zfab";
	int fabricIndex = 0;
	bool isFabricReplaced = FABRIC_API->ReplaceFabric(fabricIndex, zFabFilePath);

	if (isFabricReplaced)
		UTILITY_API->DisplayMessageBox("Failed to replace the fabric");
	else
		UTILITY_API->DisplayMessageBox("Fabric replaced");
}

void ExportCroppedRenderImage_Sample()
{
	if (!UTILITY_API)
		return;

	if (!EXPORT_API)
		return;
	
	//Set background crop as cropStatus.
	UTILITY_API->SetCropBackground(true);

	//Avatar display false.
	UTILITY_API->SetShowHideAvatar(false);

	//Zoom cloth to get better result.
	UTILITY_API->SetZoomView();

	//Export rendering image.
	EXPORT_API->ExportRenderingImage(false);
}

void AutoHang_Sample()
{
	if (!UTILITY_API)
		return;

	string assetFolderPathForCurrentVersion = UTILITY_API->GetCLOAssetFolderPath(false);
	string hangerPath = assetFolderPathForCurrentVersion + "Avatar/Hanger/Adult_Shirt_Hanger_V3.avt";
	string garmentPath = assetFolderPathForCurrentVersion + "Garment/Male_T-shirt.zpac";

	Marvelous::ImportExportOption options;

	UTILITY_API->AutoHang(hangerPath, garmentPath, 0, options);
}


extern CLO_PLUGIN_SPECIFIER void DoFunction()
{
#if TEST_ALL_FUNCTIONS | USE_EXPORT_ZPRJ_SAMPLE 
	ExportZprjSample();
#endif

#if TEST_ALL_FUNCTIONS |  USE_RENDERINGIMAGE_SAMPLE
	ExportRenderingImage_Sample();
#endif

#if TEST_ALL_FUNCTIONS |  USE_EXPORT_TECHPACK_SAMPLE
	ExportTechPack_Sample();
#endif

#if TEST_ALL_FUNCTIONS |  USE_EXPORT_OBJ_SAMPLE
	ExportOBJ_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_FABRIC_SAMPLE
	ExportFabric_Sample();
	ImportFabric_Sample();
	DeleteFabric_Sample();
	FabricMetaData_Sample();
	SetFabricName_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_PROGRESSBAR_SAMPLE
	ProgressBar_Sample();
#endif

	//#if TEST_ALL_FUNCTIONS | USE_EXPORT_SIMULATION_SAMPLE
	//	ExportSimulation_Sample();
	//#endif

#if TEST_ALL_FUNCTIONS | USE_GET_INFORMATIONS_SAMPLE
	GetInformations_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_CUSTOM_VIEW_SAMPLE
	GetCustomView_Sample();
	GetCustomViewWithZcmrTest();
#endif

#if TEST_ALL_FUNCTIONS | USE_COLORWAY_NAME_SAMPLE
	ColorwayName_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_REST_API_TEST
	HttpGetTest(); // to test GetByteArrayFromStream() function
	string baseFolder = getHomePath() + "Zpac/";
	UploadToCLOSET(baseFolder + "test.zpac"); // to test CallRESTPostWithMultipartFormData() 
#endif

#if TEST_ALL_FUNCTIONS | USE_UNICODE_FUNCTION_TEST
	UnicodeFunctionsTest();
#endif

#if TEST_ALL_FUNCTIONS | USE_ADD_COLORCHIP_TEST
	AddColorChip_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_LOAD_LIBRARY_COLOR_SWATCH_LIST_TEST
	LoadLibraryColorSwatchList_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_ADD_LIBRARY_COLOR_SWATCH_LIST_TEST
	AddLibraryColorSwatchList_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_SET_COLOR_SWATCH_LIST_ITEM_NAME_TEST
	SetColorSwatchListItemName_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_DELETE_COLOR_SWATCH_LIST_ITEM_TEST
	DeleteColorSwatchListItem_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_SET_COLOR_SWATCH_LIBRARY_TAB_NAME_TEST
	SetColorSwatchLibraryTabName_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_DELETE_COLOR_SWATCH_LIBRARY_TAB_BY_NAME_TEST
	DeleteColorSwatchLibraryTabByName_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_NEW_PROJECT_TEST
	NewProject_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_FABRIC_FILE_METADATA_TEST
	FabricFileMetaData_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_CLO_FILE_PATH_TEST
	GetCLOFilePath_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_EXPORT_TURNTABLE_IMAGES
	ExportTurntableImages_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_EXPORT_GLTF_TEST
	ExportGLTF_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_EXPORT_TURNTABLE_VIDEO
	ExportTurntableVideos_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_EXPORT_ANIMATION_VIDEO
	ExportAnimationVideos_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_READ_WRITE_METADATA_FILE //still developing
	ReadWriteMetaDataFile_Sample();
#endif

#if	TEST_ALL_FUNCTIONS | USE_SET_WINDOWS_TITLE_3D_TEST
	SetWindowsTitle3D_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_COPY_COLORWAY_TEST
	CopyColorway_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_GARMENT_INFO_TEST
	ExportGarmentInformation_Sample();
	ImportGarmentInformation_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_GARMENT_INFO_CONFIG_TEST
	ExportGarmentInformationConfigData_Sample();
	ImportGarmentInformationConfigData_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_EXPORT_TECHPACK_TO_STREAM_TEST
	ExportTechPackToStream_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_EXPORT_THUMBNAIL3D_TEST
	ExportThumbnail3D_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_EXPORT_SNAPSHOT3D_TEST
	ExportSnapshot3D_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_EXPORT_SINGLE_COLORWAY_RENDERING_IMAGE_TEST
	ExportSingleColorwayRenderingImage_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_RENDER_IMAGE_RELATED_PATHS_TEST
	GetTotalRenderImagePaths_Sample();
	GetCurrentRenderImagePaths_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_FILE_NAME_ON_RENDERING_PROPERTY_TEST
	GetFileNameOnRenderingProperty_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_COLORWAY_RELATED_INFORMATION_TEST
	GetColorwayRelatedInformation_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_SIZE_RELATED_INFORMATION_TEST
	GetSizeRelatedInformation_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_FABRIC_RELATED_INFORMATION_TEST
	GetFabricRelatedInformation_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_CHANGE_FABRIC_WITH_JSON_TEST
	ChangeFabricWithJson_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_ASSIGN_FABRIC_TO_PATTERN_TEST
	AssignFabricToPattern_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_IMPORT_ZPRJ_SAMPLE
	ImportZprj_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_IMPORT_FILE_SAMPLE
	ImportFile_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_EXPORT_ZPAC_TEST
	ExportZpac_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_AVATAR_RELATED_API_TEST
	GetAvatarCount_Test();
	GetAvatarNameList_Test();
	GetAvatarGenderList_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_PATTERN_RELATED_API_TEST
	GetPatternIndex_Test();
	GetPatternCount_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_VERSION_CHECK_API_TEST
	GetMajorVersion_Test();
	GetMinorVersion_Test();
	GetPatchVersion_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_EXPORT_GLB_TEST
	ExportGLB_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_SAVE_FABRIC_CUSTOME_THUMBNAIL_TEST
	SaveFabricCustomThumbnail_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_IMPORT_OBJ_SAMPLE
	ImportOBJ_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_IMPORT_VMP_SAMPLE
	ImportVMP_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_IMPORT_CPT_SAMPLE
	ImportCPT_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_IMPORT_VLP_SAMPLE
	ImportVLP_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_IMPORT_VRP_SAMPLE
	ImportVRP_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_FABRICINFORMATION_TEST
	UpdateFabricInformation_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_PRIMARY_FABRIC_API_TEST
	GetPrimaryFabric_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_COLORLIST_FOR_COLORWAY_TEST
	GetColorListForColorWay_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_EXPORT_POM_TEST
	ExportPOM_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_SHOW_HIDE_AVATAR_TEST
	SetShowHideAvatar_Sample();
	SetShowHideAvatarByIndex_Sample();
	IsShowAvatarByIndex_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_SCHEMATIC_RENDER_TEST
	SetSchematicRender_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_PATTERN_PIECE_AREA_TEST
	GetPatternPieceArea_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_LINE_LENGTH_TEST
	GetLineLength_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_PATTERN_INPUT_INFORMATION_TEST
	GetPatternInputInformation_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_PATTERN_BOUNDING_BOX_TEST
	GetBoundingBoxOfPattern_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_PATTERNS_BOUNDING_BOX_TEST
	GetBoundingBoxOfPatterns_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_PATTERN_PARTICLE_DISTANCE_TEST
	GetParticleDistanceOfPattern_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_PATTERN_MESH_COUNT_TEST
	GetMeshCountByType_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_PATTERN_SHRINKAGE_PERCENTAGE_TEST
	GetShrinkagePercentage_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_IMPORT_DXF_FILE_SAMPLE
	ImportDXFFile_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_UPDATE_COLOWAYS
	UpdateColorways_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_EXPORT_THUMBNAIL3D_FOR_COLORWAYS
	ExportThumbnail3DForColorways_Sample();
#endif

#if TEST_ALL_FUNCTIONS | USE_SET_PATTERN_PARTICLE_DISTANCE_TEST
	SetParticleDistanceOfPattern_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_SET_PATTERNS_PARTICLE_DISTANCE_TEST
	SetParticleDistanceOfPatterns_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_SET_MESH_TYPE_TEST
	SetMeshTypeOfPattern_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_SET_WIDTH_PATTERN_SHRINKAGE_PERCENTAGE_TEST
	SetWidthShrinkagePercentageOfPattern_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_SET_HEIGHT_PATTERN_SHRINKAGE_PERCENTAGE_TEST
	SetHeightShrinkagePercentageOfPattern_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_ARRANGEMENTLIST_TEST
	GetArrangementList_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_PATTERN_ARRANGEMENT_TEST
	GetArrangementOfPattern_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_PATTERNS_ARRANGEMENT_TEST
	GetArrangementOfPatterns_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_SET_ARRANGEMENT_SHAPE_STYLE_TEST
	SetArrangementShapeStyle_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_SET_ARRANGEMENT_POSITION_TEST
	SetArrangementPosition_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_SET_ARRANGEMENT_ORIENTATION_TEST
	SetArrangementOrientation_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_SET_ARRANGEMENT_TEST
	SetArrangement_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_EXPORT_POSE_TEST
	ExportAvatarPose_Test();
#endif

#if TEST_ALL_FUNCTIONS |  USE_EXPORT_FBX_TEST
	ExportFBX_Test();
#endif

#if TEST_ALL_FUNCTIONS |  USE_DELETE_COLORWAY_ITEM_TEST
	DeleteColorwayItem_Test();
#endif

#if TEST_ALL_FUNCTIONS |  USE_COPY_PATTERN_PIECE_POS_TEST
	CopyPatternPiecePos_Test();
#endif

#if TEST_ALL_FUNCTIONS |  USE_COPY_PATTERN_PIECE_MOVE_TEST
	CopyPatternPieceMove_Test();
#endif

#if TEST_ALL_FUNCTIONS |  USE_DELETE_PATTERN_PIECE_TEST
	DeletePatternPiece_Test();
#endif

#if TEST_ALL_FUNCTIONS |  USE_DELETE_LINE_PIECE_TEST
	DeleteLine_Test();
#endif

#if TEST_ALL_FUNCTIONS |  USE_DELETE_POINT_PIECE_TEST
	DeletePoint_Test();
#endif

#if TEST_ALL_FUNCTIONS |  USE_FLIP_PATTERN_PIECE_TEST
	FlipPatternPiece_Test();
#endif

#if TEST_ALL_FUNCTIONS |  USE_LAYER_CLONE_PATTERN_PIECE_POS_TEST
	LayerClonePatternPiecePos_Test();
#endif

#if TEST_ALL_FUNCTIONS |  USE_LAYER_CLONE_PATTERN_PIECE_MOVE_TEST
	LayerClonePatternPieceMove_Test();
#endif

#if TEST_ALL_FUNCTIONS |  USE_OFFSET_AS_INTERNAL_LINE_TEST
	OffsetAsInternalLine_Test();
#endif

#if TEST_ALL_FUNCTIONS |  USE_UNFOLD_PATTERN_PIECE_TEST
	UnfoldPatternPiece_Test();
#endif

#if TEST_ALL_FUNCTIONS |  USE_CONVER_TO_BASE_LINE_TEST
	ConvertToBaseLine_Test();
#endif

#if TEST_ALL_FUNCTIONS |  USE_CONVER_TO_INTERNAL_LINE_TEST
	ConvertToInternalLine_Test();
#endif

#if TEST_ALL_FUNCTIONS |  USE_DISTRIBUE_INTERNAL_LINES_BETWEEN_SEGMENTS_TEST
	DistribueInternalLinesbetweenSegments_Test();
#endif
 
#if TEST_ALL_FUNCTIONS | USE_IMPORT_GRAPHICSTYLE_TEST
	ImportGraphicStyle_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_REPLACE_GRAPHICSTYLE_TEST
	ReplaceGraphicStyle_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_PATTERN_PIECE_POS_TEST
	GetPatternPiecePosTest();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_PATTERN_PIECE_POS_TEST
	SetPatternPiecePosTest();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_PATTERN_PIECE_MOVE_TEST
	SetPatternPieceMoveTest();
#endif
   
#if TEST_ALL_FUNCTIONS | USE_ELASTIC_TEST          
	ElasticTest();
#endif
#if TEST_ALL_FUNCTIONS | USE_ELASTIC_STRENGTH_TEST      
	ElasticStrengthTest();
#endif
#if TEST_ALL_FUNCTIONS | USE_ELASTIC_STRENGTH_RATIO_TEST
	ElasticStrengthRatioTest();
#endif
#if TEST_ALL_FUNCTIONS | USE_ELASTIC_SEGMENT_LENGTH_TEST
	ElasticSegmentLengthTest();
#endif
#if TEST_ALL_FUNCTIONS | USE_ELASTIC_TOTAL_LENGTH_TEST  
	ElasticTotalLengthTest();
#endif
#if TEST_ALL_FUNCTIONS | USE_SHIRRING_TEST   
	ShirringTest();
#endif
#if TEST_ALL_FUNCTIONS | USE_SHIRRING_INTERVAL_TEST 
	ShirringIntervalTest();
#endif
#if TEST_ALL_FUNCTIONS | USE_SHIRRING_HEIGHT_TEST  
	ShirringHeightTest();
#endif
#if TEST_ALL_FUNCTIONS | USE_SHIRRING_EXTEND_TEST
	ShirringExtendTest();
#endif
#if TEST_ALL_FUNCTIONS | USE_SEAMTAPING_TEST
	SeamTapingTest();
#endif
#if TEST_ALL_FUNCTIONS | USE_SEAMTAPING_WIDTH_TEST 
	SeamTapingWidthTest();
#endif

#if TEST_ALL_FUNCTIONS | USE_PATTERN_PIECE_INFO_TEST
	PatternPieceInfo_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_PATTERN_PIECE_FABRIC_STYLE_INFO_TEST
	PatternPieceFabricStyleInfo_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_PATTERN_PIECE_SOLIDIFY_INFO_TEST
	GetPatternPieceSolidifyInfo_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_FABRIC_STYLE_NAME_LIST_TEST
	GetFabricStyleNameList_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_PATTERN_LAYER_TEST
	SetPatternLayer_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_PATTERN_LAYER_TEST
	GetPatternLayer_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_PATTERN_STRENGTHEN_TEST
	SetPatternStrengthen_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_PATTERN_LOCK_TEST
	SetPatternLock_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_PATTERN_HIDE_3D_TEST
	SetPatternHide3D_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_PATTERN_FREEZE_TEST
	SetPatternFreeze_Test();
#endif
	
#if TEST_ALL_FUNCTIONS | USE_ADD_SEGMENT_TOPSTITCH_TEST
	AddSegmentTopstitch_Test();
#endif
	
#if TEST_ALL_FUNCTIONS | USE_GET_TOPSTITCH_STYLE_LIST_TEST
	GetTopstitchStyleList_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_PATTERN_ASSIGNED_TOPSTITCH_COUNT_TEST
	GetPatternAssignedTopstitchCount_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_PATTERN_ASSIGNED_TOPSTITCH_STYLE_TEST
	GetPatternAssignedTopstitchStyle_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_PATTERN_ASSIGNED_TOPSTITCH_TEST
	GetPatternAssignedTopstitch_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_PATTERN_ASSIGNED_TOPSTITCH_STYLE_INDEX_TEST
	GetPatternAssignedTopstitchStyleIndex_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_PATTERN_ASSIGNED_TOPSTITCH_STYLE_TEST
	SetPatternAssignedTopstitchStyle_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_IS_PATTERN_ASSIGNED_TOPSTITCH_EXTEND_START_TEST
	IsPatternAssignedTopstitchExtendStart_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_PATTERN_ASSIGNED_TOPSTITCH_EXTEND_START_TEST
	SetPatternAssignedTopstitchExtendStart_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_IS_PATTERN_ASSIGNED_TOPSTITCH_EXTEND_END_TEST
	IsPatternAssignedTopstitchExtendEnd_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_PATTERN_ASSIGNED_TOPSTITCH_EXTEND_END_TEST
	SetPatternAssignedTopstitchExtendEnd_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_IS_PATTERN_ASSIGNED_TOPSTITCH_CURVED_TEST
	IsPatternAssignedTopstitchCurved_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_PATTERN_ASSIGNED_TOPSTITCH_CURVED_TEST
	SetPatternAssignedTopstitchCurved_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_PATTERN_ASSIGNED_TOPSTITCH_CURVED_LENGTH_TEST
	GetPatternAssignedTopstitchCurvedLength_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_PATTERN_ASSIGNED_TOPSTITCH_CURVED_LENGTH_TEST
	SetPatternAssignedTopstitchCurvedLength_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_IS_PATTERN_ASSIGNED_TOPSTITCH_CURVED_RIGHT_ANGLED_TEST
	IsPatternAssignedTopstitchCurvedRightAngled_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_PATTERN_ASSIGNED_TOPSTITCH_CURVED_RIGHT_ANGLED_TEST
	SetPatternAssignedTopstitchCurvedRightAngled_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_PATTERN_ASSIGNED_TOPSTITCH_ZOFFSET_TEST
	GetPatternAssignedTopstitchZOffset_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_PATTERN_ASSIGNED_TOPSTITCH_ZOFFSET_TEST
	SetPatternAssignedTopstitchZOffset_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_IMPORT_TOPSTITCH_STYLE_TEST
	ImportTopStitchStyle_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_CREATE_PATTERN_WITH_POINTS
	CreatePattern_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_IMPORT_AVAC_SAMPLE
	ImportAVAC_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_AVATAR_TEXTURE_SAMPLE
	SetAvatarBodyTexture_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_IMPORT_FILE_BY_OBJ_TYPE_SAMPLE
	ImportFileByObjType_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_IMPORT_FBX_SAMPLE
	ImportFBX_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_IMPORT_GLTF_SAMPLE
	ImportGLTF_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_ANIMATION_RECORDING_TEST
	SetAnimationRecording_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_CURRENT_ANIMATION_FRAME_TEST
	SetCurrentAnimationFrame_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_CURRENT_ANIMATION_FRAME_TEST
	GetCurrentAnimationFrame_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_START_ANIMATION_FRAME_TEST
	SetStartAnimationFrame_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_START_ANIMATION_FRAME_TEST
	GetStartAnimationFrame_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_END_ANIMATION_FRAME_TEST
	SetEndAnimationFrame_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_END_ANIMATION_FRAME_TEST
	GetEndAnimationFrame_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_IMPORT_SMP_SAMPLE
	ImportSMP_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_IMPORT_SUBSTANCE_FILE_AS_FACETYPE_SAMPLE
	ImportSubstanceFileAsFaceType_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_IMPORT_AS_GRAPHIC
	ImportAsGraphic();
#endif
#if TEST_ALL_FUNCTIONS | USE_IMPORT_TRIM
	ImportTrim_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_EXPORT_AVT_SAMPLE
	ExportAVT_Sample();
#endif								 	
#if TEST_ALL_FUNCTIONS | USE_SET_TEXTURE_MAPPING
	SetTextureMapping_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_SUBSTANCE_PRESET
	SetSubstancePreset_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_SUBSTANCE_RESOLUTION
	SetSubstanceResolution_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_ANNOTATION_TEST
	PatternAnnotation_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_LINKED_PATTERN_INDEX_TEST
	GetLinkedPatternIndex_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_SET_STRESS_MAP_RENDERED_STATUS
	StatusStressMap_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_SET_STRAIN_MAP_RENDERED_STATUS
	StatusStrainMap_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_REFRESH_PLUGINS
	RefreshPlugIns_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_CAM_VIEW_POINT_TEST
	SetCamViewPoint_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_USE_SAME_MATERIAL_AS_FRONT
	SetUseSameMaterialAsFront_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_USE_SAME_COLOR_AS_FRONT
	SetUseSameColorAsFront_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_SCHEMATIC_SILHOUETTE_LINE_WIDTH
	SetSchematicSilhouetteLineWidth_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_SCHEMATIC_SEAM_LINE_WIDTH
	SetSchematicSeamLineWidth_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_SCHEMATIC_INTERNAL_LINE_WIDTH
	SetSchematicInternalLineWidth_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_SCHEMATIC_TOPSTITCH_LINE_SCALE_PERCENT
	SetSchematicTopstitchLineScalePercent_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_SCHEMATIC_BRIGHTNESS
	SetSchematicBrightness_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_SHOW_SCHEMATIC_SILHOUETTE_LINE
	SetShowSchematicSilhouetteLine_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_SHOW_SCHEMATIC_SEAM_LINE
	SetShowSchematicSeamLine_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_SHOW_SCHEMATIC_INTERNAL_LINE
	SetShowSchematicInternalLine_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_SHOW_SCHEMATIC_TOPSTITCH_LINE
	SetShowSchematicTopstitchLine_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_SCHEMATIC_CLOTH_RENDER_TYPE
	SetSchematicClothRenderType_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_STYLE_LINE_COLOR
	SetStyleLineColor_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_SCHEMATIC_CLOTH_COLOR
	SetSchematicClothColor_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_CREATE_MODULAR_CATEGORY_API_SAMPLE
	CreateModularCategory_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_DELETE_MODULAR_CATEGORY_API_SAMPLE
	DeleteModularCategory_Test ();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_TOPSTITCH_STYLE_MODEL_TYPE
	GetTopstitchStyleModel_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_TOPSTITCH_STYLE_MODEL_TYPE
	SetTopstitchStyleModel_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_CREATE_ZFAB_FROM_TEXTURE
	CreateZfabFromTextures_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_COMBINE_ZFAB
	CombineZfab_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_BAKE_UV_TEXTURE
	BakeUVTexture_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_UV_PACKING
	UVPacking_Test();
#endif
	
#if TEST_ALL_FUNCTIONS | USE_GET_ROUGHNESS_CONFIG_OF_MATERIAL_IN_FABRIC
	GetRoughnessInFabric_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_ROUGHNESS_CONFIG_OF_MATERIAL_IN_FABRIC
	SetRoughnessInFabric_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_EXPORT_TRIM_SAMPLE
	ExportTrim_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_TRIM_WEIGHT
	SetTrimWeight_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_EXPORT_OBJECTBROWSER_MATERIAL_LIST
	GetObjectBrowserMaterialUsed();
#endif

#if TEST_ALL_FUNCTIONS | USE_GET_ALL_PIN_LIST
	GetPinList();
#endif
#if TEST_ALL_FUNCTIONS | USE_REMOVE_SELECTED_PIN
	int indexOfPin = 0;
	RemovePinByIndex(indexOfPin);
#endif
#if TEST_ALL_FUNCTIONS | USE_EXPORT_STD_VIEW_IMAGES
	ExportStdViewImage_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_EXPORT_STD_VIEW_IMAGES_FOR_ALL_COLORWAYS
	ExportStdViewImageForAllColorways_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_EXPORT_CUSTOM_VIEW_IMAGES
	ExportCustomViewImage_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_EXPORT_CUSTOM_VIEW_IMAGES_FOR_ALL_COLORWAYS
	ExportCustomViewImageForAllColorways_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_EXPORT_MULTI_VIEW_IMAGES
	ExportMultiViewImages_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_EXPORT_MULTI_VIEW_IMAGES_FOR_ALL_COLORWAYS
	ExportMultiViewImagesForAllColorways_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_CHANGING_GRADING_SIZE
    ChangeGradingSize();
#endif
#if TEST_ALL_FUNCTIONS | USE_REFRESH_3D_WINDOW
	Refresh3DWindow_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_COVERT_ZBLC_TO_ZMOD
	ConvertZblcToZmod_Test();
#endif

#if TEST_ALL_FUNCTIONS | USE_SET_COLORWAY_COLOR_ITEM
	SetColorwayColorItem_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_COLORWAY_COLOR_ITEM_RGB
	GetColorwayColorItemRGB_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_COLORWAY_COLOR_ITEM_PLM_ID
	GetColorwayColorItemPlmId_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_COLORWAY_COLOR_ITEM_NAME
	GetColorwayColorItemName_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_REMOVE_PLUGIN_FROM_LIST
	RemovePlugInFromList();
#endif
#if TEST_ALL_FUNCTIONS | USE_ADD_PLUGIN_FROM_FILE
	AddPlugInFromFile();
#endif
#if TEST_ALL_FUNCTIONS | USE_PLUGIN_FROM_LIST
	UsePlugInFromList();
#endif
#if TEST_ALL_FUNCTIONS | USE_TERMINATE_PLUGIN_FROM_LIST
	TerminatePlugInFromList();
#endif
#if TEST_ALL_FUNCTIONS | USE_EXPORT_POM_3D_LENGTH_TEST
	ExportPOMfor3DLength_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_DISPLACEMENT_MAP_API_TEST
    ChangeDisplacementMapValue();
#endif
#if TEST_ALL_FUNCTIONS | USE_ADD_SEAMLINE_STITCH_TEST
	AddSeamlineStitchToPattern_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_SEAMLINE_PAIR_GROUP_COUNT_TEST
	GetSeamlinePairGroupCount_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_SEAMLINE_PAIR_GOUP_NAME_TEST
	GetSeamlinePairGroupName_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_SEAMLINE_PAIR_GROUP_INDEX_FROM_NAME_TEST
	GetSeamlinePairGroupIndexFromName_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_ALL_STITCH_PROPERTY_TEST
	GetAllStitchProperty_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_ADD_SEAMLINE_PAIR_GROUP_TEST
	AddSeamlinePairGroup_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_3D_GARMENT_RENDERING_STYLE_SAMPLE
	Set3DGarmentRenderingStyle_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_EXPORT_PATTERN_JSON
	string filePath = "";
	ExportPatternJSON(filePath);
#endif
#if TEST_ALL_FUNCTIONS | USE_IMPORT_PATTERN_JSON
	string filePath = "";
	ImportPatternJSON(filePath);
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_GRADING_PAIRED_AVATAR
	int gradingIndex = 0;
	GetGradingPairedAvatar(gradingIndex);
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_REFLECTION_ROUGHNESS
	GetReflectionRoughness_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_REFLECTION_ROUGHNESS
	SetReflectionRoughness_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_REFLECTION_INTENSITY
	GetReflectionIntensity_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_REFLECTION_INTENSITY
	SetReflectionIntensity_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_METALNESS
	GetMetalness_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_METALNESS
	SetMetalness_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_NORMAL_MAP_INTENSITY
	GetNormalMapIntensity_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_NORMAL_MAP_INTENSITY
	SetNormalMapIntensity_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_MATERIAL_TYPE
	GetMaterialType_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_MATERIAL_TYPE
	SetMaterialType_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_OPACITY_INTENSITY
	GetOpacityIntensity_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_OPACITY_INTENSITY
	SetOpacityIntensity_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_TOTAL_GRAPHIC_ITEM_QUANTITY
	GetTotalGraphicItemQuantity_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_GRAPHIC_STYLE_COUNT
	GetGraphicStyleCount_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_GRAPHIC_STYLE_NAME
	GetGraphicStyleName_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_GRAPHIC_STYLE_DIMENSIONS
	GetGraphicStyleDimensions_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_GRAPHIC_STYLE_NAME
	SetGraphicStyleName_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_GRAPHIC_STYLE_DIMENSIONS
	SetGraphicStyleDimensions_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_GRAPHIC_STYLE_WIDTH
	SetGraphicStyleWidth_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_GRAPHIC_STYLE_HEIGHT
	SetGraphicStyleHeight_Test();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_BASETEXTUREMAP_IMAGE_FILE_PATH_TEST
	GetBaseTextureMapImageFilePath_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_NORMALMAP_IMAGE_FILE_PATH_TEST
	GetNormalMapImageFilePath_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_DISPLACEMENT_IMAGE_FILE_PATH_TEST
	GetDisplacementMapImageFilePath_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_OPACITYMAP_IMAGE_FILE_PATH_TEST
	GetOpacityMapImageFilePath_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_ROUGHNESSMAP_IMAGE_FILE_PATH_TEST
	GetRoughnessMapImageFilePath_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_GET_METALNESSMAP_IMAGE_FILE_PATH_TEST
	GetMetalnessMapImageFilePath_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_BASETEXTUREMAP_IMAGE_FILE_PATH_TEST
	SetBaseTextureMapImageGivenFilePath_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_NORMALMAP_IMAGE_TEST
	SetNormalMapImageGivenFilePath_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_DISPLACEMENTMAP_IMAGE_TEST
	SetDisplacementMapImageGivenFilePath_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_OPACITYMAP_IMAGE_TEST
	SetOpacityMapImageGivenFilePath_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_ROUGHNESSMAP_IMAGE_TEST
	SetRoughnessMapImageGivenFilePath_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_METALNESSMAP_IMAGE_TEST
	SetMetalnessMapImageGivenFilePath_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_SET_EXPORT_BOM_TEST
	ExportBOM_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_REPLACE_FABRIC
	ReplaceFabric_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_EXPORT_USD_TEST
	ExportUSD_Sample();
#endif
#if TEST_ALL_FUNCTIONS | USE_AUTO_HANG_TEST
	AutoHang_Sample();
#endif
}

extern CLO_PLUGIN_SPECIFIER void DoFunctionAfterLoadingCLOFile(const char* fileExtenstion)
{
	if (UTILITY_API != nullptr)
		UTILITY_API->DisplayMessageBox("DoFunctionAferLoadingProject starts... for file type -  " + string(fileExtenstion));
}

extern CLO_PLUGIN_SPECIFIER const char* GetActionName()
{
	const char* actionName = "Test Convert Modular";
#if USE_RENDERINGIMAGE_SAMPLE
	actionName = "Rendering Image Sample Plugin";
#endif

#if USE_EXPORT_TECHPACK_SAMPLE
	actionName = "Export Techpack Sample Plugin";
#endif

#if USE_EXPORT_OBJ_SAMPLE
	actionName = "Export Obj Sample Plugin";
#endif

#if USE_EXPORT_ZPRJ_SAMPLE
	actionName = "Export Zprj Sample Plugin";
#endif

#if USE_FABRIC_SAMPLE
	actionName = "Plugin with using Fabric API Sample";
#endif

#if USE_PROGRESSBAR_SAMPLE
	actionName = "Progress Bar Sample Plugin";
#endif

#if USE_GET_INFORMATIONS_SAMPLE
	actionName = "Get Information Sample Plugin";
#endif

#if USE_GET_CUSTOM_VIEW_SAMPLE
	actionName = "Get Custom View Sample Plugin";
#endif

#if USE_COLORWAY_NAME_SAMPLE
	actionName = "Colorway Name Sample Plugin";
#endif

#if USE_REST_API_TEST
	actionName = "Rest API Sample Plugin";
#endif

#if USE_UNICODE_FUNCTION_TEST
	actionName = "API with wstring Sample Plugin";
#endif

#if USE_ADD_COLORCHIP_TEST
	actionName = "Add Colorchip Sample Plugin";
#endif

#if USE_NEW_PROJECT_TEST
	actionName = "New project Sample Plugin";
#endif

#if USE_FABRIC_FILE_METADATA_TEST
	actionName = "Fabric metadata Sample Plugin";
#endif

#if USE_GET_CLO_FILE_PATH_TEST
	actionName = "CLO file path Sample Plugin";
#endif

#if USE_EXPORT_TURNTABLE_IMAGES
	actionName = "Export Turntable Images Sample Plugin";
#endif

#if USE_EXPORT_GLTF_TEST
	actionName = "Export GLTF Sample Plugin";
#endif

#if USE_EXPORT_TURNTABLE_VIDEO
	actionName = "Export Turntable Video Sample Plugin";
#endif

#if USE_READ_WRITE_METADATA_FILE
	actionName = "Metadata from file Sample Plugin";
#endif

#if USE_SET_WINDOWS_TITLE_3D_TEST
	actionName = "Set 3D Windows Title Sample Plugin";
#endif

#if USE_COPY_COLORWAY_TEST
	actionName = "Copy Colorway Sample Plugin";
#endif

#if USE_GARMENT_INFO_TEST
	actionName = "Garment Information Sample Plugin";
#endif

#if USE_GARMENT_INFO_CONFIG_TEST
	actionName = "Garment Information Config Data Plugin";
#endif

#if USE_EXPORT_ANIMATION_VIDEO
	actionName = "Export Animation Video Sample Plugin";
#endif

#if USE_IMPORT_ZPRJ_SAMPLE
	actionName = "Import Zprj Sample Plugin";
#endif

#if USE_IMPORT_FILE_SAMPLE
	actionName = "Import File Sample Plugin";
#endif

#if USE_EXPORT_ZPAC_TEST
	actionName = "Export Zpac Test";
#endif

#if USE_AVATAR_RELATED_API_TEST
	actionName = "Avatar Related API calls Test";
#endif

#if USE_EXPORT_SIMULATION_SAMPLE
	actionName = "Export Simulation Sample Test";
#endif

#if USE_EXPORT_TECHPACK_TO_STREAM_TEST
	actionName = "Export Techpack to Stream Test";
#endif

#if USE_EXPORT_THUMBNAIL3D_TEST
	actionName = "Export Thumbnail3D Test";
#endif

#if USE_EXPORT_SNAPSHOT3D_TEST
	actionName = "Export Snapshot3D Test";
#endif

#if USE_EXPORT_SINGLE_COLORWAY_RENDERING_IMAGE_TEST
	actionName = "Export Single Colorway Rendering Image Test";
#endif

#if USE_GET_RENDER_IMAGE_RELATED_PATHS_TEST
	actionName = "Get Render Image Related Path Test";
#endif

#if USE_GET_FILE_NAME_ON_RENDERING_PROPERTY_TEST
	actionName = "Get File Name on Rendering Property Test";
#endif

#if USE_GET_COLORWAY_RELATED_INFORMATION_TEST
	actionName = "Get Colorway Related Information Test";
#endif

#if USE_GET_SIZE_RELATED_INFORMATION_TEST
	actionName = "Get Size Related Information Test";
#endif

#if USE_GET_FABRIC_RELATED_INFORMATION_TEST
	actionName = "Get Fabric Related Information Test";
#endif

#if USE_CHANGE_FABRIC_WITH_JSON_TEST
	actionName = "Change Fabric with Json Test";
#endif

#if USE_ASSIGN_FABRIC_TO_PATTERN_TEST
	actionName = "Assign Fabric to Pattern Test";
#endif

#if USE_EXPORT_GLB_TEST
	actionName = "Export GLB Sample Plugin";
#endif	

#if USE_SAVE_FABRIC_CUSTOME_THUMBNAIL_TEST
	actionName = "Save Fabric Thumbnails Test";
#endif

#if USE_IMPORT_OBJ_SAMPLE
	actionName = "Import OBJ Test";
#endif

#if USE_IMPORT_VMP_SAMPLE
	actionName = "Import VMP Test";
#endif

#if USE_IMPORT_CPT_SAMPLE
	actionName = "Import CPT Test";
#endif

#if USE_IMPORT_VLP_SAMPLE
	actionName = "Import VLP Test";
#endif

#if USE_IMPORT_VRP_SAMPLE
	actionName = "Import VRP Test";
#endif

#if USE_FABRICINFORMATION_TEST
	actionName = "Fabric Information Test";
#endif

#if USE_PRIMARY_FABRIC_API_TEST
	actionName = "Primary Fabric API Test";
#endif

#if USE_GET_COLORLIST_FOR_COLORWAY_TEST
	actionName = "Get ColorListForColorway API Test";
#endif

#if USE_EXPORT_POM_TEST
	actionName = "Export POM Test";
#endif

#if USE_SHOW_HIDE_AVATAR_TEST
	actionName = "Set Show/Hide Avatar API Test";
#endif

#if USE_SCHEMATIC_RENDER_TEST
	actionName = "Set Enable/Disalbe Schematic Render API Test";
#endif

#if USE_IMPORT_DXF_FILE_SAMPLE
	actionName = "Import DXF Test";
#endif

#if USE_GET_PATTERN_PIECE_AREA_TEST
	actionName = "Get Pattern Piece Area API Test";
#endif	

#if USE_GET_LINE_LENGTH_TEST
	actionName = "Get Line Length API Test";
#endif	

#if USE_GET_PATTERN_INPUT_INFORMATION_TEST
	actionName = "Get Pattern Input Information API Test";
#endif	

#if USE_GET_PATTERN_BOUNDING_BOX_TEST
	actionName = "Get Pattern BoundingBox Size API Test";
#endif	

#if USE_GET_PATTERNS_BOUNDING_BOX_TEST
	actionName = "Get Patterns BoundingBox Size API Test";
#endif	

#if USE_GET_PATTERN_PARTICLE_DISTANCE_TEST
	actionName = "Get Pattern Particle Distance Of Pattern API Test";
#endif	

#if USE_GET_PATTERN_MESH_COUNT_TEST
	actionName = "Get Pattern Mesh Count By Type API Test";
#endif	

#if USE_GET_PATTERN_SHRINKAGE_PERCENTAGE_TEST
	actionName = "Get Pattern Shrinkage Percentage API Test";
#endif	

#if USE_UPDATE_COLOWAYS
	actionName = "Update Colorways";
#endif
  
#if USE_EXPORT_THUMBNAIL3D_FOR_COLORWAYS
	actionName = "Export Thumbnail3D For Colorways Test";
#endif

#if USE_SET_PATTERN_PARTICLE_DISTANCE_TEST
	actionName = "Set Pattern Particle Distance Of Pattern API Test";
#endif	

#if USE_SET_PATTERNS_PARTICLE_DISTANCE_TEST
	actionName = "Set Patterns Particle Distance Of Pattern API Test";
#endif	

#if USE_SET_MESH_TYPE_TEST
	actionName = "Set Mesh Type Of Pattern API Test";
#endif	

#if USE_SET_WIDTH_PATTERN_SHRINKAGE_PERCENTAGE_TEST
	actionName = "Set Width Shrinkage Percentage API Test";
#endif	

#if USE_SET_HEIGHT_PATTERN_SHRINKAGE_PERCENTAGE_TEST
	actionName = "Set Height Shrinkage Percentage API Test";
#endif	

#if USE_GET_ARRANGEMENTLIST_TEST
	actionName = "Get Arrangement List API Test";
#endif	

#if USE_GET_PATTERN_ARRANGEMENT_TEST
	actionName = "Get Arrangement Of Pattern API Test";
#endif	

#if USE_GET_PATTERNS_ARRANGEMENT_TEST
	actionName = "Get Arrangement Of Patterns API Test";
#endif	

#if USE_SET_ARRANGEMENT_SHAPE_STYLE_TEST
	actionName = "Set Arrangement Shape Style Of Pattern API Test";
#endif	

#if USE_SET_ARRANGEMENT_POSITION_TEST
	actionName = "Set Arrangement Position Of Pattern API Test";
#endif	

#if USE_SET_ARRANGEMENT_ORIENTATION_TEST
	actionName = "Set Arrangement Orientation Of Pattern API Test";
#endif	

#if USE_SET_ARRANGEMENT_TEST
	actionName = "Set Arrangement API Test";
#endif	

#if USE_EXPORT_POSE_TEST
	actionName = "Export Avatar Pose File Test";
#endif	

#if USE_EXPORT_FBX_TEST
	actionName = "Export FBX Test";
#endif

#if USE_DELETE_COLORWAY_ITEM_TEST
	actionName = "Delete Colorway Item";
#endif

#if USE_COPY_PATTERN_PIECE_POS_TEST
	actionName = "Copy Pattern Position Test";
#endif

#if USE_COPY_PATTERN_PIECE_MOVE_TEST
	actionName = "Copy Pattern Move Test";
#endif

#if USE_DELETE_PATTERN_PIECE_TEST
	actionName = "Delete Pattern Test";
#endif	

#if USE_DELETE_LINE_PIECE_TEST
	actionName = "Delete Line Test";
#endif	

#if USE_DELETE_POINT_PIECE_TEST
	actionName = "Delete Point Test";
#endif	

#if USE_FLIP_PATTERN_PIECE_TEST
	actionName = "Flip Pattern Test";
#endif

#if USE_LAYER_CLONE_PATTERN_PIECE_POS_TEST
	actionName = "Layer Clone Pattern Position Test";
#endif	

#if USE_LAYER_CLONE_PATTERN_PIECE_MOVE_TEST
	actionName = "Layer Clone Move Test";
#endif

#if USE_OFFSET_AS_INTERNAL_LINE_TEST
	actionName = "Offset As InternalLine Test";
#endif

#if USE_UNFOLD_PATTERN_PIECE_TEST
	actionName = "Unfold Pattern Piece Test";
#endif

#if USE_CONVER_TO_BASE_LINE_TEST
	actionName = "Convert To BaseLine Test";
#endif

#if USE_CONVER_TO_INTERNAL_LINE_TEST
	actionName = "Convert To InternalLine Test";
#endif

#if USE_DISTRIBUE_INTERNAL_LINES_BETWEEN_SEGMENTS_TEST
	actionName = "Distribue Internal Lines between Segments";
#endif
  
#if USE_IMPORT_GRAPHICSTYLE_TEST
	actionName = "Import Graphic Style";
#endif

#if USE_REPLACE_GRAPHICSTYLE_TEST
	actionName = "Replace Graphic Style";
#endif

#if USE_GET_PATTERN_PIECE_POS_TEST
	actionName = "Get Pattern Piece Pos";
#endif
#if USE_SET_PATTERN_PIECE_POS_TEST
	actionName = "Set Pattern Piece Pos";
#endif
#if USE_SET_PATTERN_PIECE_MOVE_TEST
	actionName = "Set Pattern Piece Move";
#endif

#if TEST_ALL_FUNCTIONS | USE_ELASTIC_TEST
	actionName = "Set Elastic";
#endif
#if TEST_ALL_FUNCTIONS | USE_ELASTIC_STRENGTH_TEST
	actionName = "Set Elastic Strength";
#endif
#if TEST_ALL_FUNCTIONS | USE_ELASTIC_STRENGTH_RATIO_TEST
	actionName = "Set Elastic Strength Ratio";
#endif
#if TEST_ALL_FUNCTIONS | USE_ELASTIC_SEGMENT_LENGTH_TEST
	actionName = "Set Elastic Segment Length";
#endif
#if TEST_ALL_FUNCTIONS | USE_ELASTIC_TOTAL_LENGTH_TEST
	actionName = "Set Elastic Total Length";
#endif
#if TEST_ALL_FUNCTIONS | USE_SHIRRING_TEST
	actionName = "Set Shirring";
#endif
#if TEST_ALL_FUNCTIONS | USE_SHIRRING_INTERVAL_TEST
	actionName = "Set Shirring Interval";
#endif
#if TEST_ALL_FUNCTIONS | USE_SHIRRING_HEIGHT_TEST
	actionName = "Set Shirring Height";
#endif
#if TEST_ALL_FUNCTIONS | USE_SHIRRING_EXTEND_TEST
	actionName = "Set Shirring Extend";
#endif
#if TEST_ALL_FUNCTIONS | USE_SEAMTAPING_TEST
	actionName = "Set Seam Taping";
#endif
#if TEST_ALL_FUNCTIONS | USE_SEAMTAPING_WIDTH_TEST
	actionName = "Set Seam Taping Width";
#endif

#if USE_PATTERN_PIECE_INFO_TEST
	actionName = "Pattern Piece Info Test";
#endif

#if USE_PATTERN_PIECE_FABRIC_STYLE_INFO_TEST
	actionName = "Pattern Piece Fabric Style Info Test";
#endif

#if USE_PATTERN_PIECE_SOLIDIFY_INFO_TEST
	actionName = "Pattern Piece Solidify Info Test";
#endif

#if USE_GET_FABRIC_STYLE_NAME_LIST_TEST
	actionName = "Get Fabric Style Name List";
#endif

#if USE_SET_PATTERN_LAYER_TEST
	actionName = "Set Pattern Layer API Test";
#endif

#if USE_GET_PATTERN_LAYER_TEST
	actionName = "Get Pattern Layer API Test";
#endif

#if USE_SET_PATTERN_STRENGTHEN_TEST
	actionName = "Set Pattern Strengthen API Test";
#endif

#if USE_SET_PATTERN_LOCK_TEST
	actionName = "Set Pattern Lock API Test";
#endif
	
#if USE_SET_PATTERN_HIDE_3D_TEST
	actionName = "Set Pattern Hide 3D API Test";
#endif

#if USE_SET_PATTERN_FREEZE_TEST
	actionName = "Set Pattern Freeze API Test";
#endif
	
#if USE_ADD_SEGMENT_TOPSTITCH_TEST
	actionName = "Add Segment topstitch API Test";
#endif

#if USE_GET_TOPSTITCH_STYLE_LIST_TEST
	actionName = "Get Topstitch Style List API Test";
#endif
	
#if USE_GET_PATTERN_ASSIGNED_TOPSTITCH_COUNT_TEST
	actionName = "Get Pattern Assigned Topstitch Count API Test";
#endif
#if USE_GET_PATTERN_ASSIGNED_TOPSTITCH_STYLE_TEST
	actionName = "Get Pattern Assigned Topstitch Style API Test";
#endif
#if USE_GET_PATTERN_ASSIGNED_TOPSTITCH_TEST
	actionName = "Get Pattern Assigned Topstitch API Test";
#endif
#if USE_GET_PATTERN_ASSIGNED_TOPSTITCH_STYLE_INDEX_TEST
	actionName = "Get Pattern Assigned Topstitch Style Index API Test";
#endif
#if USE_SET_PATTERN_ASSIGNED_TOPSTITCH_STYLE_TEST
	actionName = "Set Pattern Assigned Topstitch Style API Test";
#endif
#if USE_IS_PATTERN_ASSIGNED_TOPSTITCH_EXTEND_START_TEST
	actionName = "Is Pattern Assigned Topstitch Extend Start API Test";
#endif
#if USE_SET_PATTERN_ASSIGNED_TOPSTITCH_EXTEND_START_TEST
	actionName = "Set Pattern Assigned Topstitch Extend Start API Test";
#endif
#if USE_IS_PATTERN_ASSIGNED_TOPSTITCH_EXTEND_END_TEST
	actionName = "Is Pattern Assigned Topstitch Extend End API Test";
#endif
#if USE_SET_PATTERN_ASSIGNED_TOPSTITCH_EXTEND_END_TEST
	actionName = "Set Pattern Assigned Topstitch Extend End API Test";
#endif
#if USE_IS_PATTERN_ASSIGNED_TOPSTITCH_CURVED_TEST
	actionName = "Is Pattern Assigned Topstitch Curved API Test";
#endif
#if USE_SET_PATTERN_ASSIGNED_TOPSTITCH_CURVED_TEST
	actionName = "Set Pattern Assigned Topstitch Curved API Test";
#endif
#if USE_GET_PATTERN_ASSIGNED_TOPSTITCH_CURVED_LENGTH_TEST
	actionName = "Get Pattern Assigned Topstitch Curved Length API Test";
#endif
#if USE_SET_PATTERN_ASSIGNED_TOPSTITCH_CURVED_LENGTH_TEST
	actionName = "Set Pattern Assigned Topstitch Curved Length API Test";
#endif
#if USE_IS_PATTERN_ASSIGNED_TOPSTITCH_CURVED_RIGHT_ANGLED_TEST
	actionName = "Is Pattern Assigned Topstitch Curved Right Angled API Test";
#endif
#if USE_SET_PATTERN_ASSIGNED_TOPSTITCH_CURVED_RIGHT_ANGLED_TEST
	actionName = "Set Pattern Assigned Topstitch Curved Right Angled API Test";
#endif
#if USE_GET_PATTERN_ASSIGNED_TOPSTITCH_ZOFFSET_TEST
	actionName = "Get Pattern Assigned Topstitch Zoffset API Test";
#endif
#if USE_SET_PATTERN_ASSIGNED_TOPSTITCH_ZOFFSET_TEST
	actionName = "Set Pattern Assigned Topstitch Zoffset API Test";
#endif
#if USE_IMPORT_TOPSTITCH_STYLE_TEST
	actionName = "Import TopStitch Style API Test";
#endif
#if USE_IMPORT_AVAC_SAMPLE
	actionName = "Import AVAC File Sample";
#endif
#if USE_SET_AVATAR_TEXTURE_SAMPLE
	actionName = "Set Avatar Texture Sample";
#endif
#if USE_IMPORT_FILE_BY_OBJ_TYPE_SAMPLE
	actionName = "Import File By OBJ Type Sample";
#endif
#if USE_IMPORT_FBX_SAMPLE
	actionName = "Import FBX Sample";
#endif
#if USE_IMPORT_GLTF_SAMPLE
	actionName = "Import GLTF Sample";
#endif
#if USE_SET_ANIMATION_RECORDING_TEST
	actionName = "Set Animation Recording Test";
#endif
#if USE_SET_CURRENT_ANIMATION_FRAME_TEST
	actionName = "Set Current Animation Frame Test";
#endif
#if USE_GET_CURRENT_ANIMATION_FRAME_TEST
	actionName = "Get Current Animation Frame Test";
#endif
#if USE_SET_START_ANIMATION_FRAME_TEST
	actionName = "Set Start Animation Frame Test";
#endif
#if USE_GET_START_ANIMATION_FRAME_TEST
	actionName = "Get Start Animation Frame Test";
#endif
#if USE_SET_END_ANIMATION_FRAME_TEST
	actionName = "Set End Animation Frame Test";
#endif
#if USE_GET_END_ANIMATION_FRAME_TEST
	actionName = "Get End Animation Frame Test";
#endif
#if USE_IMPORT_SMP_SAMPLE
	actionName = "Import SMP Sample";
#endif
#if USE_IMPORT_SUBSTANCE_FILE_AS_FACETYPE_SAMPLE
	actionName = "Import Substance File As FaceType Sample";
#endif
#if USE_IMPORT_AS_GRAPHIC
	actionName = "Import as Graphic Sample";
#endif
#if USE_IMPORT_TRIM
	actionName = "Import Trim";
#endif
#if USE_EXPORT_AVT_SAMPLE
	actionName = "Export AVT Sample";
#endif
#if USE_SET_TEXTURE_MAPPING
	actionName = "Set Texture Mapping Sample";
#endif
#if USE_SET_SUBSTANCE_PRESET
	actionName = "Set Substance Preset Sample";
#endif
#if USE_SET_SUBSTANCE_RESOLUTION
	actionName = "Set Substance Resolution Sample";
#endif
#if USE_REFRESH_PLUGINS
	actionName = "Refresh plugins Sample";
#endif
#if USE_SET_CAM_VIEW_POINT_TEST
	actionName = "Set Cam View Point Sample";
#endif
#if USE_SET_USE_SAME_MATERIAL_AS_FRONT
	actionName = "Set Use Same Material As Front";
#endif
#if USE_SET_USE_SAME_COLOR_AS_FRONT
	actionName = "Set Use Same Color As Front";
#endif
#if USE_SET_SCHEMATIC_SILHOUETTE_LINE_WIDTH
	actionName = "Set Schematic Silhouette Line Width";
#endif
#if USE_SET_SCHEMATIC_SEAM_LINE_WIDTH
	actionName = "Set Schematic SeamLine Width";
#endif
#if USE_SET_SCHEMATIC_INTERNAL_LINE_WIDTH
	actionName = "Set Schematic Internal Line Width";
#endif
#if USE_SET_SCHEMATIC_TOPSTITCH_LINE_SCALE_PERCENT
	actionName = "Set Schematic Topstitch Line Scale Percent";
#endif
#if USE_SET_SCHEMATIC_BRIGHTNESS
	actionName = "Set Schematic Brightness";
#endif
#if USE_SET_SHOW_SCHEMATIC_SILHOUETTE_LINE
	actionName = "Set Show Schematic Silhouette Line";
#endif
#if USE_SET_SHOW_SCHEMATIC_SEAM_LINE
	actionName = "Set Show Schematic SeamLine Test";
#endif
#if USE_SET_SHOW_SCHEMATIC_INTERNAL_LINE
	actionName = "Set Show Schematic Internal Line";
#endif
#if USE_SET_SHOW_SCHEMATIC_TOPSTITCH_LINE
	actionName = "Set Show Schematic Topstitch Line";
#endif
#if USE_SET_SCHEMATIC_CLOTH_RENDER_TYPE
	actionName = "Set Schematic Cloth Render Type";
#endif
#if USE_SET_STYLE_LINE_COLOR
	actionName = "Set Style Line Color";
#endif
#if USE_SET_SCHEMATIC_CLOTH_COLOR
	actionName = "Set Schematic Cloth Color";
#endif

#if USE_CREATE_MODULAR_CATEGORY_API_SAMPLE
	actionName = "Create Modular Category Sample";
#endif

#if USE_DELETE_MODULAR_CATEGORY_API_SAMPLE
	actionName = "Delete Modular Category Sample";
#endif

#if USE_GET_TOPSTITCH_STYLE_MODEL_TYPE
	actionName = "Get Topstitch Type Sample Plugin";
#endif
#if USE_SET_TOPSTITCH_STYLE_MODEL_TYPE
	actionName = "Set Topstitch Type Sample Plugin";
#endif
#if USE_CREATE_ZFAB_FROM_TEXTURE
	actionName = "Create Zfab From Textures";
#endif
#if USE_COMBINE_ZFAB
	actionName = "Combine Zfab";
#endif
#if USE_BAKE_UV_TEXTURE
	actionName = "Bake UV Texture Sample Plugin";
#endif
#if USE_UV_PACKING
	actionName = "Packing UV";
#endif
#if USE_GET_ROUGHNESS_CONFIG_OF_MATERIAL_IN_FABRIC
	actionName = "Get Roughness values in fabric";
#endif
#if USE_SET_ROUGHNESS_CONFIG_OF_MATERIAL_IN_FABRIC
	actionName = "Set Roughness values in fabric";
#endif
#if USE_EXPORT_TRIM_SAMPLE
	actionName = "Export Trim";
#endif
#if USE_SET_TRIM_WEIGHT
	actionName = "Set Trim Weight";
#endif
#if USE_EXPORT_OBJECTBROWSER_MATERIAL_LIST
	actionName = "Get Materials in Object Browser ";
#endif
#if USE_REMOVE_SELECTED_PIN
	actionName = "Remove Selected Pin";
#endif

#if USE_GET_ALL_PIN_LIST
	actionName = "Get All Pin List";
#endif
#if USE_EXPORT_STD_VIEW_IMAGES
	actionName = "Exports Standard View Images Based on the Provided View Index";
#endif
#if USE_EXPORT_STD_VIEW_IMAGES_FOR_ALL_COLORWAYS
	actionName = "Exports Standard View Images Based on the Provided View Index for all Colorways";
#endif
#if USE_EXPORT_CUSTOM_VIEW_IMAGES
	actionName = "Reads ZCMR file details and Exports custom View Image";
#endif
#if USE_EXPORT_CUSTOM_VIEW_IMAGES_FOR_ALL_COLORWAYS
	actionName = "Reads ZCMR file details and Exports custom View Image for all Colorways";
#endif
#if USE_EXPORT_MULTI_VIEW_IMAGES
	actionName = "Reads MVS file details and Exports Multi View Images";
#endif
#if USE_EXPORT_MULTI_VIEW_IMAGES_FOR_ALL_COLORWAYS
	actionName = "Reads MVS file details and Exports Multi View Images for all Colorways";
#endif
#if USE_CHANGING_GRADING_SIZE
	actionName = "Change Grading Size";
#endif
#if USE_REFRESH_3D_WINDOW
	actionName = "Refresh 3D Window";
#endif
#if USE_COVERT_ZBLC_TO_ZMOD
	actionName = "Convert Zblc to Zmod"
#endif

#if USE_SET_COLORWAY_COLOR_ITEM
	actionName = "Set The Color of the Color Item In Colorway";
#endif
#if USE_GET_COLORWAY_COLOR_ITEM_RGB
	actionName = "Get The RGB Color Value of the Color Item In Colorway";
#endif
#if USE_GET_COLORWAY_COLOR_ITEM_PLMID
	actionName = "Get PLM Id of the Color Item In Colorway";
#endif
#if USE_GET_COLORWAY_COLOR_ITEM_NAME
	actionName = "Get Name of the Color Item In Colorway";
#endif
#if USE_REMOVE_PLUGIN_FROM_LIST
	actionName = "Remove Plug In From List";
#endif
#if USE_ADD_PLUGIN_FROM_FILE
	actionName = "Add Plug In From File";
#endif
#if USE_PLUGIN_FROM_LIST
	actionName = "Use Plug In From List";
#endif
#if USE_TERMINATE_PLUGIN_FROM_LIST
	actionName = "Terminate Plug In From List";
#endif
#if USE_DISPLACEMENT_MAP_API_TEST
    actionName = "Get/set displacement map or its values";
#endif
#if USE_EXPORT_POM_3D_LENGTH_TEST
	actionName = "Export POM 3DLength Test";
#endif
#if USE_ADD_SEAMLINE_STITCH_TEST
	actionName = "Add SeamlineStitch Test";
#endif
#if USE_GET_SEAMLINE_PAIR_GROUP_COUNT_TEST
	actionName = "Get SeamlinePairGroup Count";
#endif
#if USE_GET_SEAMLINE_PAIR_GOUP_NAME_TEST
	actionName = "Get SeamlinePairGroup Name";
#endif
#if USE_GET_SEAMLINE_PAIR_GROUP_INDEX_FROM_NAME_TEST
	actionName = "Get SemalinePairGroup Index From Name";
#endif
#if USE_GET_ALL_STITCH_PROPERTY_TEST
	actionName = "Get All Stitch Property Test";
#endif
#if USE_ADD_SEAMLINE_PAIR_GROUP_TEST
	actionName = "Add Seamline Pair Group Test";
#endif
#if USE_SET_3D_GARMENT_RENDERING_STYLE_SAMPLE
	actionName = "Set 3D Garment Rendering Style Test";
#endif
#if USE_GET_GRADING_PAIRED_AVATAR
	actionName = "Get Grading Paired Avatar";
#endif
#if USE_EXPORT_PATTERN_JSON
	actionName = "Export Pattern in JSON";
#endif
#if USE_IMPORT_PATTERN_JSON
	actionName = "Import Pattern in JSON";
#endif
#if USE_LOAD_LIBRARY_COLOR_SWATCH_LIST_TEST
	actionName = "Load colorSwatchList bundle"
#endif
#if USE_ADD_LIBRARY_COLOR_SWATCH_LIST_TEST
	actionName = "Add color swatch list to library"
#endif
#if USE_SET_COLOR_SWATCH_LIST_ITEM_NAME_TEST
	actionName = "Set color swatch list item name"
#endif
#if USE_DELETE_COLOR_SWATCH_LIST_ITEM_TEST
	actionName = "Delete color swatch list item"
#endif
#if USE_SET_COLOR_SWATCH_LIBRARY_TAB_NAME_TEST
	actionName = "Set color swatch library tab name"
#endif
#if USE_DELETE_COLOR_SWATCH_LIBRARY_TAB_BY_NAME_TEST
	actionName = "Delete colorSwatchList by name"
#endif
#if USE_GET_TOTAL_GRAPHIC_ITEM_QUANTITY
	actionName = "Get total graphic item quantity"
#endif
#if USE_GET_GRAPHIC_STYLE_COUNT
	actionName = "Get graphic style count"
#endif
#if USE_GET_GRAPHIC_STYLE_NAME
	actionName = "Get graphic style name"
#endif
#if USE_GET_GRAPHIC_STYLE_DIMENSIONS
	actionName = "Get graphic style dimensions"
#endif
#if USE_SET_GRAPHIC_STYLE_NAME
		actionName = "Set graphic style name"
#endif
#if USE_SET_GRAPHIC_STYLE_DIMENSIONS
		actionName = "Set graphic style dimensions"
#endif
#if USE_SET_GRAPHIC_STYLE_WIDTH
		actionName = "Set graphic style width"
#endif
#if USE_SET_GRAPHIC_STYLE_HEIGHT
		actionName = "Set graphic style height"
#endif
#if USE_GET_BASETEXTUREMAP_IMAGE_FILE_PATH_TEST
		actionName = "Get BaseTexture Map"
#endif
#if USE_GET_NORMALMAP_IMAGE_FILE_PATH_TEST
		actionName = "Get Normal Map"
#endif
#if USE_GET_DISPLACEMENT_IMAGE_FILE_PATH_TEST
		actionName = "Get Displacement Map"
#endif
#if USE_GET_OPACITYMAP_IMAGE_FILE_PATH_TEST
		actionName = "Get Opacity Map"
#endif
#if USE_GET_ROUGHNESSMAP_IMAGE_FILE_PATH_TEST
		actionName = "Get Roughness Map"
#endif
#if USE_GET_METALNESSMAP_IMAGE_FILE_PATH_TEST
		actionName = "Get Metalness Map"
#endif
#if USE_SET_BASETEXTUREMAP_IMAGE_FILE_PATH_TEST
		actionName = "Set Base Texture Map"
#endif
#if USE_SET_NORMALMAP_IMAGE_TEST
		actionName = "Set Normal Map"
#endif
#if USE_SET_DISPLACEMENTMAP_IMAGE_TEST
		actionName = "Set Displacement Map"
#endif
#if USE_SET_OPACITYMAP_IMAGE_TEST
		actionName = "Set Opacity Map"
#endif
#if USE_SET_ROUGHNESSMAP_IMAGE_TEST
		actionName = "Set Roughness Map"
#endif
#if USE_SET_METALNESSMAP_IMAGE_TEST
		actionName = "Set Metalness Map"
#endif


#if TEST_ALL_FUNCTIONS // should be here at the last position
	actionName = "All Tests";
#endif

	return actionName;
}

extern CLO_PLUGIN_SPECIFIER const char* GetObjectNameTreeToAddAction()
{
	const char* objetNameTree = "menuPlugins / menuPlug_In";

	return objetNameTree;
}

extern CLO_PLUGIN_SPECIFIER int GetPositionIndexToAddAction()
{
	return 1; // 0: Above, 1: below (default = 1)
}