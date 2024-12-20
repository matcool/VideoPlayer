#ifndef _VIDEO_PLAYER_HPP
#define _VIDEO_PLAYER_HPP

#include <Geode/Bindings.hpp>
#include <queue>

#ifdef GEODE_IS_WINDOWS
    #ifdef _VIDEO_PLAYER_EXPORTING
        #define VIDEO_PLAYER_DLL __declspec(dllexport)
    #else
        #define VIDEO_PLAYER_DLL __declspec(dllimport)
    #endif
#else
    #define VIDEO_PLAYER_DLL
#endif

namespace videoplayer {
    class VIDEO_PLAYER_DLL VideoPlayer : public cocos2d::CCNodeRGBA {
        struct Impl;
        std::unique_ptr<Impl> m_impl;
        friend struct Impl;

        cocos2d::CCSize m_dimensions;
        unsigned int m_textures[3]; // y, cb, cr
        std::queue<float> m_samples;

        FMOD::Channel* m_channel;
        FMOD::Sound* m_sound;

        bool m_paused;
        bool m_loop;
        bool m_stopped;
        float m_volume = 1.0f;

    protected:
        bool init(std::filesystem::path const& path, bool loop);
        
        void initAudio();

        virtual void update(float delta) override;
        virtual void draw() override;

        VideoPlayer();
        virtual ~VideoPlayer();
        virtual void onExit() override;
    public:

        /**
         * @brief Allocates and initializes a video player.
         * 
         * @param path Path to the video file (Could use Mod::get()->getResourcesDir() / "file.mpg").
         * @param loop Whether or not playback should loop upon completion.
         * @return A new initialized video player
         */
        static VideoPlayer* create(std::filesystem::path const& path, bool loop=false);

        /**
         * @brief Sets the content height of the video player, maintaining aspect ratio
         * 
         * @param height The new content height for the video player
         */
        void setHeight(float height);

        /**
         * @brief Sets the content width of the video player, maintaining aspect ratio
         * 
         * @param width The new content width for the video player
         */
        void setWidth(float width);

        /**
         * @brief Modifies the content size of the video player to fit a given size, maintaining aspect ratio
         * 
         * @param size The size to fill
         */
        void fillSize(cocos2d::CCSize size);

        /**
         * @brief Sets the volume of playback.
         * 
         * @param volume The new volume
         */
        void setVolume(float volume);

        /**
         * @brief Pauses playback
         * 
         */
        void pause();

        /**
         * @brief Resumes playback
         * 
         */
        void resume();

        /**
         * @brief Toggles playback.
         * 
         */
        void toggle();

        /**
         * @brief Returns whether playback is paused.
         * 
         * @return The playback status
         */
        bool isPaused();
    };
}

#endif