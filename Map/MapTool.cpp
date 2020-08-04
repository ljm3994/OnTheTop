#include "stdafx.h"
#include "MapTool.h"

HRESULT MapTool::init()
{
	ShowCursor(true);

	//맵툴셋팅
	m_Map = new Map();
	ImgSet();
	SelectImage = 0;
	TileSettingOpen = false;
	m_Object = TileObject::OBJECT_EMPTY;
	_SelectType = TileProperty::PASS;
	m_ObjectSelect = false;
	m_bStateSelect[0] = true;
	m_bStateSelect[1] = false;
	m_SelectFramx = 0;
	m_SelectFramy = 0;
	m_Mode = MODE_DRAW;
	//지형그리기 버튼으로 초기화

	ImageKey1 = "Map";
	ImageKey2 = "Map";
	m_PassView = false;
	m_TileView = false;
	m_TileIndexView = false;

	X = m_Map->Getm_Info()->GetTileMaxX();
	Y = m_Map->Getm_Info()->GetTileMaxY();
	W = m_Map->Getm_Info()->GetTileWidth();
	H = m_Map->Getm_Info()->GetTileHeight();

	return S_OK;
}

void MapTool::release(void)
{
}

MapTool::MapTool()
{
}

void MapTool::update(void)
{
	m_Map->Setm_ViewTile(m_TileView);
	m_Map->Setm_ViewPass(m_PassView);
	m_Map->Setm_ViewIndex(m_TileIndexView);
	if (KEYMANAGER->StayKeyDown(VK_LBUTTON) && !ImGui::GetIO().WantCaptureMouse) this->setMap();
	
	if (KEYMANAGER->StayKeyDown(VK_RIGHT))
	{
		g_ptCam.x += 100 * g_ETime;
	}
	if (KEYMANAGER->StayKeyDown(VK_LEFT))
	{
		g_ptCam.x -= 100 * g_ETime;
	}

	if (KEYMANAGER->StayKeyDown(VK_DOWN))
	{
		g_ptCam.y -= 100 * g_ETime;
	}
	if (KEYMANAGER->StayKeyDown(VK_UP))
	{
		g_ptCam.y += 100 * g_ETime;
	}
}

void MapTool::render(void)
{

	m_Map->render();

#ifdef _DEBUG
	ImGuiSetting();
#endif
}

void MapTool::ImgSet()
{
	ImageInfo info1;
	info1.ImageName = "Map";
	info1.MaxFrameX = 18;
	info1.MaxFrameY = 4;
	info1.FrameSizeX = 32.0f;
	info1.FrameSizey = 64.0f;
	info1.ImageWitdh = 256.0f;
	info1.ImageHegiht = 576.0f;
	m_ImageInfo.emplace_back(info1);
	ImageInfo info2;
	info2.ImageName = "FortressMap";
	info2.MaxFrameX = 3;
	info2.MaxFrameY = 6;
	info2.FrameSizeX = 32.0f;
	info2.FrameSizey = 30.0f;
	info2.ImageWitdh = 94.0f;
	info2.ImageHegiht = 171.0f;
	m_ImageInfo.emplace_back(info2);
	info2.ImageName = "FortressMap2";
	info2.MaxFrameX = 3;
	info2.MaxFrameY = 3;
	info2.FrameSizeX = 30.0f;
	info2.FrameSizey = 36.0f;
	info2.ImageWitdh = 92.0f;
	info2.ImageHegiht = 108.0f;
	m_ImageInfo.emplace_back(info2);
	info2.ImageName = "TopDoor";
	info2.MaxFrameX = 4;
	info2.MaxFrameY = 4;
	info2.FrameSizeX = 31.0f;
	info2.FrameSizey = 32.0f;
	info2.ImageWitdh = 125.0f;
	info2.ImageHegiht = 129.0f;
	m_ImageInfo.emplace_back(info2);
	info2.ImageName = "Top";
	info2.MaxFrameX = 10;
	info2.MaxFrameY = 2;
	info2.FrameSizeX = 31.0f;
	info2.FrameSizey = 32.0f;
	info2.ImageWitdh = 319.0f;
	info2.ImageHegiht = 65.0f;
	m_ImageInfo.emplace_back(info2);
}

void MapTool::setMap(void)
{
	m_Map->setMap(m_SelectFramx, m_SelectFramy, m_Mode, m_ImageInfo[SelectImage].ImageName, _SelectType, m_ObjectSelect, m_Object, m_ImageInfo[SelectImage].ImageName);
}

#pragma region ImGui세팅 부분
void MapTool::ImGuiSetting()
{
	bool pOpen = true;
	ImGuiStyle& style = ImGui::GetStyle();
	static bool enable_extra_decorations = false;
	float child_height = ImGui::GetTextLineHeight() + style.ScrollbarSize + style.WindowPadding.y * 2.0f;
	static bool SaveOpen = false;
	static bool LoadOpen = false;
	ImGuiWindowFlags child_flags = ImGuiWindowFlags_HorizontalScrollbar | (enable_extra_decorations ? ImGuiWindowFlags_AlwaysVerticalScrollbar : 0 | ImGuiWindowFlags_MenuBar);

	if (TileSettingOpen) ImGuiTileSettingMenu(&TileSettingOpen);

	if (!ImGui::Begin("MapTool", &pOpen, child_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			if (ImGui::MenuItem("TileSetting", NULL, &TileSettingOpen)) {}

			ImGui::EndMenu();
		}
		
		ImGui::EndMenuBar();
	}
	
	ImGuiMain();
	ImGui::End();
}

void MapTool::ImGuiMain()
{
	bool pOpen = true;

	if (ImGui::CollapsingHeader("MapTool"))
	{
		if (ImGui::TreeNode("Images"))
		{
			ImTextureID my_tex_id = IMGMANAGER->GetImage(m_ImageInfo[SelectImage].ImageName)->Getm_TexturId();
			float my_tex_w = m_ImageInfo[SelectImage].ImageWitdh;
			float my_tex_h = m_ImageInfo[SelectImage].ImageHegiht;

			ImGui::Text("%.0fx%.0f", my_tex_w, my_tex_h);
			static int pressed_count = 0;
			for (int i = 0; i < m_ImageInfo[SelectImage].MaxFrameX; i++)
			{
				for (int j = 0; j < m_ImageInfo[SelectImage].MaxFrameY; j++)
				{
					ImGui::PushID(j + (i * m_ImageInfo[SelectImage].MaxFrameY));
					int frame_padding = -1;     // -1 = uses default padding
					if (ImGui::ImageButton(my_tex_id, ImVec2(m_ImageInfo[SelectImage].FrameSizeX, m_ImageInfo[SelectImage].FrameSizey), ImVec2((m_ImageInfo[SelectImage].FrameSizeX * i) / my_tex_w, ((m_ImageInfo[SelectImage].FrameSizey * j) / my_tex_h)), ImVec2((m_ImageInfo[SelectImage].FrameSizeX * (i + 1)) / my_tex_w, (m_ImageInfo[SelectImage].FrameSizey * (j + 1) / my_tex_h)), frame_padding, ImVec4(1, 1, 1, 1.0f)))
					{
						m_SelectFramx = i;
						m_SelectFramy = j;
					}
					ImGui::PopID();
					ImGui::SameLine();
				}
				ImGui::NewLine();
			}
			float scroll_y = ImGui::GetScrollY();
			float scroll_max_y = ImGui::GetScrollMaxY();
			ImGui::Text("Select Image");
			ImGui::Image(my_tex_id, ImVec2(30, 30), ImVec2((30.0f * m_SelectFramx) / my_tex_w, ((30.0f * m_SelectFramy) / my_tex_h)), ImVec2((30.0f * (m_SelectFramx + 1)) / my_tex_w, (30.0f * (m_SelectFramy + 1) / my_tex_h)));
			if (ImGui::Button("Prev"))
			{
				if (SelectImage > 0)
				{
					SelectImage--;
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Next"))
			{
				if (SelectImage < m_ImageInfo.size() - 1)
				{
					SelectImage++;
				}
			}
			ImGui::NewLine();
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Tile State Type"))
		{
			if (ImGui::Checkbox("PASS", &m_bStateSelect[0]))
			{
				if (m_bStateSelect[0])
				{
					m_bStateSelect[1] = false;
					_SelectType = TileProperty::PASS;
				}
			}
			if (ImGui::Checkbox("NONPASS", &m_bStateSelect[1]))
			{
				if (m_bStateSelect[1])
				{
					m_bStateSelect[0] = false;
					_SelectType = TileProperty::NONPASS;
				}
			}
			if (!m_bStateSelect[0] && !m_bStateSelect[1])
			{
				_SelectType = TileProperty::EMPTY;
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Object Type"))
		{
			if (ImGui::Checkbox("Object", &m_ObjectSelect))
			{
			}
			if (m_ObjectSelect)
			{
				static int selected = -1;
				char buf[5][255];
				sprintf_s(buf[0], "EMPTY");
				sprintf_s(buf[1], "DOOR");
				sprintf_s(buf[2], "TRAP");
				sprintf_s(buf[3], "Scaffolding");
				sprintf_s(buf[4], "ETC");
				for (int n = 0; n < 5; n++)
				{
					if (ImGui::Selectable(buf[n], selected == n))
						selected = n;
				}
				m_Object = (TileObject)selected;
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Draw Tool"))
		{
			static int item_current = 0;
			ImGui::Combo("Tool", &item_current, "Draw\0Remove\0\0");
			m_Mode = (Mode)item_current;
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Draw Option"))
		{
			if (ImGui::Checkbox("PASSView", &m_PassView))
			{
			}
			if (ImGui::Checkbox("TileView", &m_TileView))
			{
			}
			if (ImGui::Checkbox("TileIndexView", &m_TileIndexView))
			{
			}
			ImGui::TreePop();
		}
		if (ImGui::Button("Save"))
			ImGui::OpenPopup("Save?");
		if (ImGui::BeginPopupModal("Save?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("Save File Name Input\n\n");
			ImGui::Separator();

			//static int dummy_i = 0;
			//ImGui::Combo("Combo", &dummy_i, "Delete\0Delete harder\0");

			static bool dont_ask_me_next_time = false;
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
			static char buf[255] = "";
			ImGui::PopStyleVar();
			ImGui::InputText("UTF-8 input", buf, IM_ARRAYSIZE(buf));
			if (ImGui::Button("OK", ImVec2(120, 0)))
			{
				strcat_s(buf, ".map");
				m_Map->SaveMap(buf);
				ImGui::CloseCurrentPopup();
			}
			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(120, 0)))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Load"))
			ImGui::OpenPopup("Load?");
		if (ImGui::BeginPopupModal("Load?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("Load File Name Input\n\n");
			ImGui::Separator();

			//static int dummy_i = 0;
			//ImGui::Combo("Combo", &dummy_i, "Delete\0Delete harder\0");

			static bool dont_ask_me_next_time = false;
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
			static char buf[255] = "";
			ImGui::PopStyleVar();
			ImGui::InputText("UTF-8 input", buf, IM_ARRAYSIZE(buf));
			
			if (ImGui::Button("OK", ImVec2(120, 0)))
			{
				strcat_s(buf, ".map");
				m_Map->LoadMap(buf);
				ImGui::CloseCurrentPopup();
			}
			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(120, 0)))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
}

void MapTool::ImGuiTileSettingMenu(bool * Popen)
{
	if (!ImGui::Begin("TileSetting", Popen))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	ImGui::InputInt("MaxTileX", &X);
	ImGui::InputInt("MaxTileY", &Y);
	ImGui::InputFloat("MaxTileWidth", &W);
	ImGui::InputFloat("MaxTileHeight", &H);
	if (ImGui::Button("Apple"))
		ImGui::OpenPopup("Apple?");

	if (ImGui::BeginPopupModal("Apple?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Tile Info Change!\n\n");
		ImGui::Separator();

		//static int dummy_i = 0;
		//ImGui::Combo("Combo", &dummy_i, "Delete\0Delete harder\0");

		static bool dont_ask_me_next_time = false;
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
		ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
		ImGui::PopStyleVar();

		if (ImGui::Button("OK", ImVec2(120, 0))) 
		{ 
			m_Map->SetMaxTile(X, Y, W, H);
			X = m_Map->Getm_Info()->GetTileMaxX();
			Y = m_Map->Getm_Info()->GetTileMaxY();
			W = m_Map->Getm_Info()->GetTileWidth();
			H = m_Map->Getm_Info()->GetTileHeight();
			ImGui::CloseCurrentPopup(); 
		}
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) 
		{ 
			ImGui::CloseCurrentPopup(); 
		}
		ImGui::EndPopup();
	}
	ImGui::End();
}


#pragma endregion


