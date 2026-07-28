#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include "lvgl_display.h"
#include "gif/lvgl_gif.h"

#include <esp_lcd_panel_io.h>
#include <esp_lcd_panel_ops.h>


class OledDisplay : public LvglDisplay {
private:
    esp_lcd_panel_io_handle_t panel_io_ = nullptr;
    esp_lcd_panel_handle_t panel_ = nullptr;

    lv_obj_t* top_bar_ = nullptr;
    lv_obj_t* status_bar_ = nullptr;
    lv_obj_t* content_ = nullptr;
    lv_obj_t* content_left_ = nullptr;
    lv_obj_t* content_right_ = nullptr;
    lv_obj_t* container_ = nullptr;
    lv_obj_t* side_bar_ = nullptr;
    lv_obj_t *emotion_label_ = nullptr;
    lv_obj_t* chat_message_label_ = nullptr;

    // --- Emotion full-screen GIF (Assets/EmojiCollection) ---
    lv_obj_t* emotion_image_ = nullptr;   // Ảnh/GIF chiếm trọn màn hình khi có emoji trong EmojiCollection
    lv_obj_t* subtitle_bg_ = nullptr;     // Thanh nền đen cho phụ đề, đè lên emotion_image_
    lv_obj_t* subtitle_label_ = nullptr;  // Text phụ đề hiển thị trên subtitle_bg_
    LvglGif* emotion_gif_ = nullptr;      // Trình phát GIF hiện tại (nullptr nếu ảnh tĩnh hoặc đang ở chế độ fallback)
    bool emotion_fullscreen_ = false;     // true khi đang ở chế độ full-screen emotion (đã ẩn container_/status_bar_)

    void ShowEmotionFullscreen(bool show);

    virtual bool Lock(int timeout_ms = 0) override;
    virtual void Unlock() override;

    void SetupUI_128x64();
    void SetupUI_128x32();

public:
    OledDisplay(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_handle_t panel, int width, int height, bool mirror_x, bool mirror_y);
    ~OledDisplay();

    virtual void SetupUI() override;
    virtual void SetChatMessage(const char* role, const char* content) override;
    virtual void SetEmotion(const char* emotion) override;
    virtual void SetTheme(Theme* theme) override;
};

#endif // OLED_DISPLAY_H