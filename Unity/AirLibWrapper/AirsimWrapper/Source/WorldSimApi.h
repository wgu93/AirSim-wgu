#pragma once

#include "api/WorldSimApiBase.hpp"
#include "./SimMode/SimModeBase.h"
#include "AirSimStructs.hpp"

class WorldSimApi : public msr::airlib::WorldSimApiBase
{
public:
    typedef msr::airlib::Pose Pose;
    typedef msr::airlib::Vector3r Vector3r;
    typedef msr::airlib::MeshPositionVertexBuffersResponse MeshPositionVertexBuffersResponse;

    WorldSimApi(SimModeBase* simmode, std::string vehicle_name);
    virtual ~WorldSimApi();

    // ------ Level setting apis ----- //
    virtual bool loadLevel(const std::string& level_name) override { return false; };
    virtual std::string spawnObject(std::string& object_name, const std::string& load_component, const Pose& pose, const Vector3r& scale, bool physics_enabled) override { return ""; };
    virtual bool destroyObject(const std::string& object_name) override { return false; };

    virtual bool isPaused() const override;
    virtual void reset() override;
    virtual void pause(bool is_paused) override;
    virtual void continueForTime(double seconds) override;
    virtual void continueForFrames(uint32_t frames) override;
    virtual void setTimeOfDay(bool is_enabled, const std::string& start_datetime, bool is_start_datetime_dst,
                              float celestial_clock_speed, float update_interval_secs, bool move_sun) override;

    virtual void enableWeather(bool enable) override;
    virtual void setWeatherParameter(WeatherParameter param, float val) override;

    virtual bool setSegmentationObjectID(const std::string& mesh_name, int object_id, bool is_name_regex = false) override;
    virtual int getSegmentationObjectID(const std::string& mesh_name) const override;
    virtual void printLogMessage(const std::string& message,
                                 const std::string& message_param = "", unsigned char severity = 0) override;

    virtual std::unique_ptr<std::vector<std::string>> swapTextures(const std::string& tag, int tex_id = 0, int component_id = 0, int material_id = 0) override;
    virtual std::vector<std::string> listSceneObjects(const std::string& name_regex) const override;
    virtual Pose getObjectPose(const std::string& object_name) const override;

    virtual Vector3r getObjectScale(const std::string& object_name) const override;
    Vector3r getObjectScaleInternal(const std::string& object_name) const;
    virtual bool setObjectPose(const std::string& object_name, const Pose& pose, bool teleport) override;
    virtual bool setObjectScale(const std::string& object_name, const Vector3r& scale) override;

    virtual bool runConsoleCommand(const std::string& command) override;

    //----------- Plotting APIs ----------/
    virtual void simFlushPersistentMarkers() override;
    virtual void simPlotPoints(const std::vector<Vector3r>& points, const std::vector<float>& color_rgba, float size, float duration, bool is_persistent) override;
    virtual void simPlotLineStrip(const std::vector<Vector3r>& points, const std::vector<float>& color_rgba, float thickness, float duration, bool is_persistent) override;
    virtual void simPlotLineList(const std::vector<Vector3r>& points, const std::vector<float>& color_rgba, float thickness, float duration, bool is_persistent) override;
    virtual void simPlotArrows(const std::vector<Vector3r>& points_start, const std::vector<Vector3r>& points_end, const std::vector<float>& color_rgba, float thickness, float arrow_size, float duration, bool is_persistent) override;
    virtual void simPlotStrings(const std::vector<std::string>& strings, const std::vector<Vector3r>& positions, float scale, const std::vector<float>& color_rgba, float duration) override;
    virtual void simPlotTransforms(const std::vector<Pose>& poses, float scale, float thickness, float duration, bool is_persistent) override;
    virtual void simPlotTransformsWithNames(const std::vector<Pose>& poses, const std::vector<std::string>& names, float tf_scale, float tf_thickness, float text_scale, const std::vector<float>& text_color_rgba, float duration) override;
    virtual std::vector<MeshPositionVertexBuffersResponse> getMeshPositionVertexBuffers() const override;

    // Recording APIs
    virtual void startRecording() override;
    virtual void stopRecording() override;
    virtual bool isRecording() const override;

    virtual void setWind(const Vector3r& wind) const override;
    virtual bool createVoxelGrid(const Vector3r& position, const int& x_size, const int& y_size, const int& z_size, const float& res, const std::string& output_file) override;
    virtual bool addVehicle(const std::string& vehicle_name, const std::string& vehicle_type, const Pose& pose, const std::string& pawn_path = "") override;

    virtual std::string getSettingsString() const override;

private:
    SimModeBase* simmode_;
    std::string vehicle_name_;
};
