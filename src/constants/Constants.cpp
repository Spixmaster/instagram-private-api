#include "ig/constants/Constants.h"
#include <string>
#include <iostream>

namespace ig
{
	const std::string Constants::version = "0.5.24";
	const std::string Constants::release = "20.Jun.2020";

	const std::string Constants::ig_api_url = "https://i.instagram.com/api/v1/";
	const std::string Constants::ig_version = "130.0.0.31.121";
	const std::string Constants::ig_sig_key_version = "4";
	const std::string Constants::ig_sig_key = "f0bdfd5332d66a64d5e04965e6a7ade67c4e2cfc57ea38f0083c0400640a5e20";
	const std::string Constants::bloks_version_id = "0e9b6d9c0fb2a2df4862cd7f46e3f719c55e9f90c20db0e5d95791b66f43b367";
	const std::string Constants::x_ig_capabilities = "3brTvwM=";
	const std::string Constants::x_ig_app_id = "567067343352427";
	const int Constants::app_refresh_interval = 3600;
	const int Constants::log_lns = 500;

	const std::string Constants::qe_sync_experiments = "ig_android_fci_onboarding_friend_search,ig_android_device_detection_info_upload,ig_android_account_linking_upsell_universe,ig_android_direct_main_tab_universe_v2,ig_android_sign_in_help_only_one_account_family_universe,ig_android_sms_retriever_backtest_universe,ig_android_direct_add_direct_to_android_native_photo_share_sheet,ig_android_spatial_account_switch_universe,ig_growth_android_profile_pic_prefill_with_fb_pic_2,ig_account_identity_logged_out_signals_global_holdout_universe,ig_android_prefill_main_account_username_on_login_screen_universe,ig_android_login_identifier_fuzzy_match,ig_android_mas_remove_close_friends_entrypoint,ig_android_video_render_codec_low_memory_gc,ig_android_custom_transitions_universe,ig_android_push_fcm,multiple_account_recovery_universe,ig_android_show_login_info_reminder_universe,ig_android_email_fuzzy_matching_universe,ig_android_one_tap_aymh_redesign_universe,ig_android_direct_send_like_from_notification,ig_android_suma_landing_page,ig_android_prefetch_debug_dialog,ig_android_smartlock_hints_universe,ig_android_black_out,ig_activation_global_discretionary_sms_holdout,ig_android_video_ffmpegutil_pts_fix,ig_android_multi_tap_login_new,ig_save_smartlock_universe,ig_android_caption_typeahead_fix_on_o_universe,ig_android_enable_keyboardlistener_redesign,ig_android_nux_add_email_device,ig_android_direct_remove_view_mode_stickiness_universe,ig_android_hide_contacts_list_in_nux,ig_android_new_users_one_tap_holdout_universe,ig_android_mas_notification_badging_universe,ig_android_secondary_account_in_main_reg_flow_universe,ig_android_secondary_account_creation_universe,ig_android_account_recovery_auto_login,ig_android_pwd_encrytpion,ig_android_sim_info_upload,ig_android_shorten_sac_for_one_eligible_main_account_universe,ig_android_mobile_http_flow_device_universe,ig_android_hide_fb_button_when_not_installed_universe,ig_android_targeted_one_tap_upsell_universe,ig_android_gmail_oauth_in_reg,ig_android_vc_interop_use_test_igid_universe,ig_android_notification_unpack_universe,ig_android_quickcapture_keep_screen_on,ig_android_registration_confirmation_code_universe,ig_android_device_based_country_verification,ig_android_log_suggested_users_cache_on_error,ig_android_reg_modularization_universe,ig_android_device_verification_separate_endpoint,ig_android_universe_noticiation_channels,ig_android_hsite_prefill_new_carrier,ig_android_one_login_toast_universe,ig_android_retry_create_account_universe,ig_android_family_apps_user_values_provider_universe,ig_android_reg_nux_headers_cleanup_universe,ig_android_get_cookie_with_concurrent_session_universe,ig_android_device_info_foreground_reporting,ig_android_shortcuts_2019,ig_android_device_verification_fb_signup,ig_android_onetaplogin_optimization,ig_android_passwordless_account_password_creation_universe,ig_android_black_out_toggle_universe,ig_video_debug_overlay,ig_android_ask_for_permissions_on_reg,ig_assisted_login_universe,ig_android_security_intent_switchoff,ig_android_device_info_job_based_reporting,ig_android_add_account_button_in_profile_mas_universe,ig_android_passwordless_auth,ig_android_direct_main_tab_account_switch,ig_android_recovery_one_tap_holdout_universe,ig_android_modularized_dynamic_nux_universe,ig_android_sac_follow_from_other_accounts_nux_universe,ig_android_fb_account_linking_sampling_freq_universe,ig_android_fix_sms_read_lollipop,ig_android_access_flow_prefill";
	const std::string Constants::qe_sync_experiments2 = "ig_android_push_notifications_settings_redesign_universe,ig_hashtag_display_universe,ig_android_shopping_checkout_signaling,ig_android_video_ssim_fix_pts_universe,coupon_price_test_ad4ad_instagram_resurrection_universe,ig_android_live_rendering_looper_universe,ig_shopping_checkout_improvements_universe,ig_android_mqtt_cookie_auth_memcache_universe,ig_android_video_player_memory_leaks,ig_android_stories_seen_state_serialization,ig_android_stories_music_search_typeahead,android_ard_ig_use_brotli_effect_universe,ig_android_delayed_comments,ig_android_direct_mutation_manager_media_3,ig_android_gif_preview_quality_universe,ig_smb_ads_holdout_2019_h1_universe,ig_fb_graph_differentiation,ig_android_shopping_bag_null_state_v1,ig_memory_manager_universe,ig_android_stories_share_extension_video_segmentation,ig_android_vc_migrate_to_bluetooth_v2_universe,ig_android_igtv_crop_top,ig_android_direct_reshare_chaining,instagram_ns_qp_prefetch_universe,ig_shopping_merchant_profile_bag_android,ig_android_separate_empty_feed_su_universe,ig_android_zero_rating_carrier_signal,ig_direct_holdout_h1_2019,ig_explore_2019_h1_destination_cover,ig_android_biz_ranked_requests_universe,ig_android_explore_recyclerview_universe,ig_android_show_muted_accounts_page,ig_android_image_pdq_calculation,ig_android_vc_service_crash_fix_universe,ig_camera_android_subtle_filter_universe,ig_android_direct_add_member_dialog_universe,ig_android_viewpoint_stories_public_testing,ig_graph_management_h2_2019_universe,ig_android_growth_fci_team_holdout_universe,android_camera_core_cpu_frames_sync,ig_android_photo_creation_large_width,ig_android_save_all,ig_android_ttcp_improvements,ig_shopping_bag_universe,ig_android_quick_promote_universe,ig_ar_shopping_camera_android_universe,ig_android_recyclerview_binder_group_enabled_universe,ig_android_stories_viewer_tall_android_cap_media_universe,ig_android_video_exoplayer_2,ig_interactions_project_daisy,native_contact_invites_universe,ig_android_dash_script,ig_android_insights_media_hashtag_insight_universe,ig_rn_branded_content_settings_approval_on_select_save,ig_camera_fast_tti_universe,ig_android_account_insights_shopping_content_universe,ig_android_render_thread_memory_leak_holdout,ig_android_automated_logging,ig_threads_clear_notifications_on_has_seen,ig_android_camera_effect_gallery_prefetch,ig_android_bullying_warning_system_2019h2,ig_share_to_story_toggle_include_shopping_product,ig_android_interactions_verified_badge_on_comment_details,ig_android_fix_ppr_thumbnail_url,ig_android_camera_reduce_file_exif_reads,ig_android_stories_blacklist,ig_payments_billing_address,ig_android_fs_new_gallery_hashtag_prompts,ig_android_sidecar_segmented_streaming_universe,ig_camera_android_gyro_senser_sampling_period_universe,ig_android_xposting_feed_to_stories_reshares_universe,ig_emoji_render_counter_logging_universe,ig_android_ufiv3_holdout,ig_android_flexible_contact_and_category_for_creators,ig_android_image_upload_quality_universe,ig_android_enable_zero_rating,ig_android_direct_leave_from_group_message_requests,ig_promote_add_payment_navigation_universe,igqe_cx_direct_two_tab_unread_indicator,ig_android_unfollow_reciprocal_universe,ig_android_keyword_serp_recyclerview,ig_android_story_ads_performance_universe_1,ig_android_stories_viewer_modal_activity,ig_android_publisher_stories_migration,ig_android_story_import_intent,ig_android_stories_context_sheets_universe,ig_android_stories_vpvd_container_module_fix,instagram_android_profile_follow_cta_context_feed,ig_biz_graph_connection_universe,ig_android_stories_boomerang_v2_universe,ig_android_vc_cowatch_universe,ig_android_nametag,ig_hashtag_creation_universe,ig_android_live_qa_viewer_v1_universe,ig_shopping_insights_wc_copy_update_android,ig_android_stories_music_lyrics_pre_capture,android_cameracore_fbaudio_integration_ig_universe,ig_android_camera_stopmotion,ig_android_igtv_reshare,ig_android_explore_reel_loading_state,ig_android_wellbeing_timeinapp_v1_universe,ig_android_profile_cta_v3,ig_end_of_feed_universe,ig_android_mainfeed_generate_prefetch_background,ig_android_feed_ads_ppr_universe,ig_android_igtv_feed_sharing_universe,ig_xposting_mention_reshare_stories,ig_android_vc_shareable_moments_universe,ig_android_igtv_watch_later,ig_android_shopping_product_metadata_on_product_tiles_universe,ig_android_video_qp_logger_universe,ig_android_frx_highlight_cover_reporting_qe,ig_email_sent_list_universe,ig_android_follow_request_button_improvements_universe,ig_android_media_streaming_sdk_universe,ig_android_cover_frame_upload_skip_story_raven_universe,ig_android_stories_video_prefetch_kb,ig_android_camera_post_smile_face_first_universe,ig_android_optic_use_new_bitmap_photo_api,ig_inventory_connections,ig_android_album_picker_with_section_headers_universe,ig_android_canvas_cookie_universe,ig_android_stories_disable_highlights_media_preloading,ig_android_effect_gallery_post_capture_universe,ig_android_branded_content_ads_universe,ig_promote_lotus_universe,ig_android_video_streaming_upload_universe,ig_android_raven_video_segmented_upload_raven_only_universe,ig_android_partial_share_sheet,ig_android_product_tag_hint_dots,ig_android_story_sharing_holdout,ig_android_camera_tti_improvements,ig_android_show_self_followers_after_becoming_private_universe,ig_interactions_h1_2019_team_holdout_universe,ig_camera_android_release_drawing_view_universe,ig_android_music_story_fb_crosspost_universe,ig_android_payments_growth_promote_payments_in_payments,ig_carousel_bumped_organic_impression_client_universe,ig_android_ad_async_ads_universe,ig_biz_post_approval_nux_universe,instagram_pcp_qp_redesign_universe,ig_android_ig_personal_account_to_fb_page_linkage_backfill,ig_android_jp_multi_media_edit_redesign_universe,ig_android_persistent_nux,ig_android_crash_fix_detach_from_gl_context,ig_android_branded_content_upsell_keywords_extension,ig_camera_thread_colour_filter,ig_android_vc_ringscreen_timeout_universe,ig_android_edit_location_page_info,ig_android_stories_project_eclipse,ig_direct_android_bubble_system,ig_android_shopping_pdp_product_videos,ig_camera_android_segmentation_v106_igdjango_universe,ig_android_camera_recents_gallery_modal,ig_promote_are_you_sure_universe,ig_camera_android_new_effect_gallery_entry_point_universe,ig_android_frx_creation_question_responses_reporting,ig_android_li_session_chaining,ig_android_create_mode_memories_see_all,ig_android_feed_post_warning_universe,ig_android_search_remove_null_state_sections,ig_camera_android_device_capabilities_experiment,ig_mprotect_code_universe,ig_view_preallocation_universe,ig_android_video_visual_quality_score_based_abr,ig_android_audience,ig_explore_2018_post_chaining_account_recs_dedupe_universe,ig_android_stories_video_seeking_audio_bug_fix,ig_android_insights_holdout,ig_android_do_not_show_social_context_for_likes_page_universe,ig_android_context_feed_recycler_view,ig_fb_notification_universe,ig_android_feed_post_sticker,ig_android_inline_editing_local_prefill,ig_android_direct_use_refactored_sender_avatar,ig_android_story_bottom_sheet_music_mas,ig_android_search_condensed_search_icons,ig_android_video_abr_universe,ig_android_unify_graph_management_actions,ig_android_own_profile_sharing_universe,ig_android_vc_cowatch_media_share_universe,ig_challenge_general_v2,ig_android_place_signature_universe,ig_android_direct_inbox_cache_universe,ig_android_ig_branding_in_fb_universe,ig_direct_android_mentions_all_universe,ig_android_business_promote_tooltip,ig_android_follow_requests_ui_improvements,ig_android_video_ssim_fix_compare_frame_index,ig_android_wellbeing_support_frx_hashtags_reporting,ig_android_direct_aggregated_media_and_reshares,ig_android_story_camera_share_to_feed_universe,ig_android_story_bottom_sheet_clips_single_audio_mas,ig_android_fb_follow_server_linkage_universe,igqe_pending_tagged_posts,ig_android_self_following_v2_universe,ig_android_stories_viewer_reply_box_placeholder_copy,ig_android_direct_view_more_qe,ig_android_churned_find_friends_redirect_to_discover_people,ig_android_iab_holdout_universe,ig_vp9_hd_blacklist,ig_android_memory_use_logging_universe,ig_android_stories_send_client_reels_on_tray_fetch_universe,ig_android_live_use_rtc_upload_universe,ig_android_delay_on_sticker_search_universe,ig_android_multi_dex_class_loader_v2,ig_commerce_platform_ptx_bloks_universe,ig_android_live_ama_viewer_universe,ig_smb_ads_holdout_2018_h2_universe,ig_android_camera_post_smile_low_end_universe,ig_cameracore_android_camera2_focus_after_first_frame,ig_android_profile_follow_tab_hashtag_row_universe,ig_android_watch_and_more_redesign,igtv_feed_previews,ig_android_video_raven_bitrate_ladder_universe,ig_android_live_realtime_comments_universe,ig_android_recipient_picker,ig_smb_ads_holdout_2019_h2_universe,ig_android_purx_native_checkout_universe,ig_android_integrity_sprint_universe,ig_android_account_insights_shopping_metrics_universe,ig_android_apr_lazy_build_request_infra,ig_android_business_transaction_in_stories_creator,ig_cameracore_android_new_optic_camera2_galaxy,ig_android_wellbeing_support_frx_igtv_reporting,ig_android_branded_content_appeal_states,ig_stories_infeed,ig_android_location_integrity_universe,ig_android_realtime_improve_dispatch_universe,ig_video_experimental_encoding_consumption_universe,ig_android_iab_autofill,ig_android_creator_quick_reply_universe,ig_android_biz_story_to_fb_page_improvement,ig_shopping_checkout_improvements_v2_universe,ig_android_direct_thread_target_queue_universe,ig_android_mediauri_parse_optimization,ig_android_branded_content_insights_disclosure,ig_android_stories_ssi_interstitial_qe,ig_android_stories_samsung_sharing_integration,ig_android_create_page_on_top_universe,ig_android_interactions_daisy_client_fallback,ig_iab_use_default_intent_loading,ig_android_camera_focus_v2,ig_adapter_leak_universe,ig_discovery_holdout_2019_h1_universe,ig_android_wellbeing_support_frx_comment_reporting,ig_android_insights_post_dismiss_button,ig_android_viewmaster_arengine_memory_pinning_improvement,ig_xposting_biz_feed_to_story_reshare,ig_android_user_url_deeplink_fbpage_endpoint,ig_android_use_action_sheet_for_profile_overflow,ig_android_wellbeing_support_frx_cowatch_reporting,ig_android_ad_holdout_watchandmore_universe,ig_promote_interactive_poll_sticker_igid_universe,ig_android_feed_cache_update,ig_android_follow_request_button_new_ui,ig_android_explore_use_shopping_endpoint,ig_android_image_upload_skip_queue_only_on_wifi,ig_android_igtv_pip,ig_android_ad_watchbrowse_carousel_universe,ig_android_camera_new_post_smile_universe,ig_android_direct_message_reactions,ig_android_shopping_signup_redesign_universe,ig_shopping_pdp_more_related_product_section,ig_android_experimental_onetap_dialogs_universe,ig_android_remove_unfollow_dialog_universe,ig_android_stories_sundial_creation_ar_effects,ig_android_fix_main_feed_su_cards_size_universe,ig_android_direct_multi_upload_universe,ig_explore_2019_h1_video_autoplay_resume,ig_promote_django_error_handling,ig_android_multi_capture_camera,ig_android_video_upload_quality_qe1,ig_android_follow_requests_copy_improvements,ig_android_save_collaborative_collections,coupon_price_test_boost_instagram_media_acquisition_universe,ig_android_video_outputsurface_handlerthread_universe,ig_android_country_code_fix_universe,ig_android_stories_music_overlay,ig_android_multi_thread_sends,ig_android_low_latency_consumption_universe,ig_android_render_output_surface_timeout_universe,ig_android_big_foot_foregroud_reporting,ig_android_unified_iab_logging_universe,ig_graph_chain_unfollow_universe,ig_aggregated_quick_reactions,ig_android_shopping_pdp_post_purchase_sharing,ig_threads_app_close_friends_integration,ig_branded_content_settings_unsaved_changes_dialog,ig_android_realtime_mqtt_logging,ig_android_lock_unlock_dex,ig_android_rainbow_hashtags,ig_android_no_bg_effect_tray_live_universe,ig_android_create_mode_templates,ig_android_direct_block_from_group_message_requests,ig_android_react_native_universe_kill_switch,ig_android_viewpoint_occlusion,ig_android_logged_in_delta_migration,ig_android_push_reliability_universe,ig_android_stories_gallery_video_segmentation,ig_explore_android_saved_collection_entrypoint,ig_android_igtv_first_frame_cover,ig_android_action_sheet_migration_universe,ig_android_igtv_cribs,ig_jp_holdout_2019_h2,ig_android_interactions_fix_activity_feed_ufi,ig_android_direct_business_holdout,ig_android_vc_direct_inbox_ongoing_pill_universe,ig_android_xposting_upsell_directly_after_sharing_to_story,ig_android_insights_native_post_universe,ig_android_dual_destination_quality_improvement,ig_android_camera_focus_low_end_universe,ig_android_camera_hair_segmentation_universe,ig_android_ads_data_preferences_universe,ig_android_follow_button_in_story_viewers_list,ig_android_vc_background_call_toast_universe,ig_hashtag_following_holdout_universe,ig_promote_default_destination_universe,ig_disable_fsync_universe,ig_android_direct_media_latency_optimizations,mi_viewpoint_viewability_universe,ig_android_live_egl10_compat,android_ard_ig_download_manager_v2,ig_direct_reshare_sharesheet_ranking,ig_shopping_checkout_ig_funded_incentives,ig_android_video_upload_transform_matrix_fix_universe,ig_android_fb_url_universe,ig_android_le_videoautoplay_disabled,ig_android_reel_raven_video_segmented_upload_universe,ig_android_promote_native_migration_universe,invite_friends_by_messenger_in_setting_universe,ig_android_fb_sync_options_universe,ig_android_insights_activity_tab_native_universe,ig_android_stories_skip_seen_state_update_for_direct_stories,text_mode_text_overlay_refactor_universe,ig_android_aggressive_media_cleanup,ig_android_recommend_accounts_destination_routing_fix,ig_android_startupmanager_refactor,ig_android_enable_automated_instruction_text_ar,ig_android_multi_author_story_reshare_universe,ig_android_building_aymf_universe,ig_android_direct_inbox_vm_actions,ig_android_internal_sticker_universe,ig_traffic_routing_universe,ig_android_stories_discussion_sticker_universe,ig_android_downloadable_json_universe,ig_camera_async_gallerycontroller_universe,ig_android_direct_state_observer,ig_android_search_usl,ig_android_page_claim_deeplink_qe,ig_android_camera_effects_order_universe,ig_android_business_tokenless_stories_xposting,ig_android_logging_metric_universe_v2,ig_android_network_onbehavior_change_fix,ig_android_xposting_newly_fbc_people,ig_android_visualcomposer_inapp_notification_universe,ig_android_do_not_show_social_context_on_follow_list_universe,ig_android_contact_point_upload_rate_limit_killswitch,ig_android_webrtc_encoder_factory_universe,ig_android_wellbeing_support_frx_direct_reporting,ig_android_qpl_class_marker,ig_android_sso_kototoro_app_universe,ig_android_camera_3p_in_post,ig_android_ar_effect_sticker_consumption_universe,ig_android_direct_unread_count_badge,ig_android_profile_thumbnail_impression,ig_android_igtv_autoplay_on_prepare,ig_android_list_adapter_prefetch_infra,ig_branded_content_tagging_upsell,ig_shopping_size_selector_redesign,ig_android_live_ama_universe,ig_android_external_gallery_import_affordance,ig_search_hashtag_content_advisory_remove_snooze,ig_android_kitkat_segmented_upload_universe,ig_android_direct_new_gallery,ig_payment_checkout_info,ig_android_video_raven_streaming_upload_universe,ig_android_vc_explicit_intent_for_notification,ig_stories_ads_delivery_rules,ig_business_new_value_prop_universe,ig_android_feed_defer_on_interactions,ig_android_vio_pipeline_universe,ig_discovery_holdout_universe,ig_android_product_tag_suggestions,ig_android_direct_import_google_photos2,ig_direct_feed_media_sticker_universe,ig_android_gallery_grid_controller_folder_cache,ig_android_igtv_upload_error_messages,ig_android_self_profile_suggest_business_main,ig_android_suggested_users_background,ig_android_ads_bottom_sheet_report_flow,ig_android_login_onetap_upsell_universe,ig_android_iris_improvements,ig_camera_android_feed_effect_attribution_universe,ig_android_test_not_signing_address_book_unlink_endpoint,ig_close_friends_home_v2,ig_android_search_nearby_places_universe,ig_graph_management_production_h2_2019_holdout_universe,ig_ei_option_setting_universe,ig_android_jp_line_share_universe,ig_android_browser_ads_page_content_width_universe,ig_android_test_remove_button_main_cta_self_followers_universe,ig_android_stories_viewer_prefetch_improvements,ig_android_livewith_liveswap_optimization_universe,ig_android_camera_leak,ig_android_wellbeing_support_frx_live_reporting,ig_android_jit,ig_stories_rainbow_ring,ig_android_place_search_profile_image,android_cameracore_safe_makecurrent_ig,ig_android_vc_egl10_compat,ig_android_ar_effect_sticker_universe,ig_android_whats_app_contact_invite_universe,ig_android_igtv_home_icon,ig_android_xposting_reel_memory_share_universe,ig_android_profile_unified_follow_view,ig_android_video_upload_hevc_encoding_universe,ig_android_mentions_suggestions,instagram_shopping_hero_carousel_visual_variant_consolidation,ig_android_vc_face_effects_universe,ig_android_fbpage_on_profile_side_tray,ig_android_shimmering_loading_state,ig_android_igtv_refresh_tv_guide_interval,ig_android_hashtag_remove_share_hashtag,igdirect_android_animate_inbox_list_changes,ig_android_feed_delivery_refactor,ig_android_feed_interactions_carousel_overscoll,ig_android_fb_profile_integration_fbnc_universe,ig_branded_content_tagging_approval_request_flow_brand_side_v2,ig_shopping_checkout_2x2_platformization_universe,ig_android_direct_bump_active_threads,ig_android_xposting_dual_destination_shortcut_fix,ig_android_wellbeing_support_frx_profile_reporting,ig_android_show_create_content_pages_universe,ig_android_igsystrace_universe,ig_android_search_register_recent_store,ig_feed_content_universe,ig_android_hashtag_limit,ig_android_disk_usage_logging_universe,ig_android_save_home_create_collection,ig_android_video_product_specific_abr,ig_android_stories_layout_universe,ig_android_wellbeing_support_frx_feed_posts_reporting,ig_android_sharedpreferences_qpl_logging,ig_android_vc_cpu_overuse_universe,ig_android_invite_list_button_redesign_universe,ig_android_react_native_email_sms_settings_universe,ig_ads_experience_holdout_2019_h2,ig_hero_player,ag_family_bridges_2018_h2_holdout,ig_promote_net_promoter_score_universe,ig_android_recents_and_edit_flow,ig_android_save_auto_sharing_to_fb_option_on_server,aymt_instagram_promote_flow_abandonment_ig_universe,ig_android_whitehat_options_universe,ig_android_keyword_media_serp_page,ig_android_delete_ssim_compare_img_soon,ig_close_friends_list_suggestions,ig_android_personal_user_xposting_destination_fix,ig_android_story_multiple_media_import,ig_android_felix_video_upload_length,android_cameracore_preview_frame_listener2_ig_universe,ig_android_direct_message_follow_button,ig_android_video_raven_passthrough,ig_stories_ads_media_based_insertion,ig_android_analytics_background_uploader_schedule,ig_camera_android_boomerang_attribution_universe,ig_android_igtv_browse_long_press,ig_android_fix_reshare_xposting_killswitch_universe,ig_threads_sanity_check_thread_viewkeys,ig_android_igtv_stories_preview,ig_discovery_2019_h2_holdout_universe,ig_android_stories_quick_react_gif_universe,ig_android_ig_personal_account_xpost_eligibility_from_server,ig_android_stories_weblink_creation,ig_android_story_bottom_sheet_top_clips_mas,ig_profile_company_holdout_h2_2018,ig_android_jp_reel_tray_location_sticker_text_universe,ig_android_stories_remote_sticker_search,ig_android_ads_manager_pause_resume_ads_universe,ig_android_direct_reel_fetching,ig_android_vc_capture_universe,ig_android_optic_face_detection,ig_android_interactions_nav_to_permalink_followup_universe,ig_android_save_to_collections_flow,ig_android_direct_segmented_video,ig_android_explore_grid_prefetch,instagram_stories_time_fixes,ig_android_direct_mark_as_read_notif_action,ig_android_not_interested_secondary_options,ig_android_jp_saved_collection_map_universe,ig_android_product_breakdown_post_insights,ig_business_integrity_ipc_universe,ig_android_hide_contacts_list,ig_android_temp_file_cleanup,ig_android_wellbeing_support_frx_stories_reporting,ig_android_direct_selfie_stickers,ig_android_smplt_universe,ig_android_vc_missed_call_call_back_action_universe,ig_cameracore_android_new_optic_camera2,ig_android_secondary_inbox_universe,ig_android_fbc_upsell_on_dp_first_load,ig_android_feed_short_session_new_post_pill,ig_android_rename_share_option_in_dialog_menu_universe,ig_android_stories_sundial_creation_universe,saved_collections_cache_universe,ig_android_business_attribute_sync,ig_camera_android_bg_processor,ig_android_dropframe_manager,ig_android_ad_stories_scroll_perf_universe,ig_android_direct_default_group_name,ig_android_video_live_trace_universe,ig_android_tango_cpu_overuse_universe,ig_android_direct_wellbeing_message_reachability_settings,ig_android_unfollow_from_main_feed_v2,ig_android_self_story_setting_option_in_menu,qe_android_direct_vm_view_modes,android_ard_ig_cache_size,ig_android_flexible_profile_universe,ufi_share,ig_android_direct_remix_visual_messages,ig_quick_story_placement_validation_universe,ig_android_custom_story_import_intent,ig_android_live_qa_broadcaster_v1_universe,ig_android_search_impression_logging_viewpoint,ig_android_downloadable_fonts_universe,ig_android_view_info_universe,ig_android_camera_upsell_dialog,ig_android_business_transaction_in_stories_consumer,ig_android_dead_code_detection,ig_android_promotion_insights_bloks,ig_android_tagging_activity_video_preview,ig_android_ad_watchbrowse_universe,ig_android_pbia_proxy_profile_universe,ig_android_qp_kill_switch,ig_android_new_follower_removal_universe,instagram_android_stories_sticker_tray_redesign,ig_android_branded_content_access_tag,ig_camera_effect_frx_categories_universe,ig_android_business_cross_post_with_biz_id_infra,ig_android_direct_delete_or_block_from_message_requests,ig_android_fix_push_setting_logging_universe,ig_android_photo_invites,ig_interactions_h2_2019_team_holdout_universe,ig_android_reel_tray_item_impression_logging_viewpoint,ig_android_direct_left_aligned_navigation_bar,ig_android_stories_reshare_reply_msg,ig_close_friends_v4,ig_android_ads_history_universe,ig_promote_media_picker_universe,ig_direct_holdout_h2_2018,ig_android_sidecar_report_ssim,ig_android_wait_for_app_initialization_on_push_action_universe,ig_android_pending_media_file_registry,ig_android_wab_adjust_resize_universe,ig_promote_ctd_post_insights_universe,ig_camera_android_facetracker_v12_universe,ig_sim_api_analytics_reporting,ig_android_promote_content_change_universe,ig_android_interest_follows_universe,ig_android_ig_to_fb_sync_universe,ig_badge_dedup_universe,ig_android_ar_background_effect_universe,ig_android_jp_map_location_sticker_universe,ig_android_audience_control,ig_android_stories_cross_sharing_to_fb_holdout_universe,shop_home_hscroll_see_all_button_universe,ig_android_refresh_empty_feed_su_universe,ig_android_ad_view_ads_native_universe,ig_android_branded_content_tag_redesign_organic,ig_camera_android_paris_filter_universe,ig_android_igtv_whitelisted_for_web,ig_android_viewmaster_dial_ordering_universe,ig_company_profile_holdout,ig_android_throttled_search_requests,ig_rti_inapp_notifications_universe,ig_android_vc_join_timeout_universe,ig_shop_directory_entrypoint,ig_android_igtv_browse_button,ig_android_feed_core_ads_2019_h1_holdout_universe,ig_close_friends_v4_global,ig_android_share_publish_page_universe,ig_direct_max_participants,ig_promote_hide_local_awareness_universe,ar_engine_audio_fba_integration_instagram,ig_android_explore_lru_cache,ig_android_graphql_survey_new_proxy_universe,ig_android_music_browser_redesign,ig_android_disable_manual_retries,ig_android_qr_code_nametag,ig_android_fs_creation_flow_tweaks,ig_android_viewmaster_ar_memory_improvements,ig_android_claim_location_page,ig_android_direct_inbox_recently_active_presence_dot_universe,ig_android_save_to_collections_bottom_sheet_refactor,ig_android_stories_gutter_width_universe,ig_android_promotion_manager_migration_universe,ig_android_story_ads_2019_h1_holdout_universe,ig_android_create_mode_tap_to_cycle,ig_timestamp_public_test,ig_android_fb_profile_integration_universe,ig_android_shopping_bag_optimization_universe,android_ig_cameracore_aspect_ratio_fix,ig_android_feed_auto_share_to_facebook_dialog,ig_android_skip_button_content_on_connect_fb_universe,ig_android_igtv_cribs_creation_universe,ig_android_igtv_explore2x2_viewer,ig_android_video_dup_request_timeout,ig_android_network_perf_qpl_ppr,ig_camera_android_focus_attribution_universe,ig_android_core_search_2019_h2,ig_android_comment_warning_non_english_universe,ig_android_stories_music_line_by_line_cube_reveal_lyrics_sticker,ig_android_iab_clickid_universe,ig_android_interactions_hide_keyboard_onscroll,ig_early_friending_holdout_universe,ig_android_profile_lazy_load_carousel_media,ig_android_stories_question_sticker_music_format,ig_pacing_overriding_universe,ig_explore_reel_ring_universe,ig_android_explore_peek_redesign_universe,ig_android_ard_ptl_universe,ig_graph_evolution_holdout_universe,ig_android_wishlist_reconsideration_universe,ig_android_q3lc_transparency_control_settings,ig_stories_selfie_sticker,ig_android_sso_use_trustedapp_universe,ig_android_stories_music_lyrics,ig_android_camera_formats_ranking_universe,ig_android_spark_studio_promo,ig_android_stories_music_awareness_universe,ard_ig_broti_effect,ig_android_camera_class_preloading,ig_android_expanded_xposting_upsell_directly_after_sharing_story_universe,ig_background_prefetch,ig_camera_android_focus_in_post_universe,ig_android_time_spent_dashboard,ig_android_emoji_util_universe_3,ig_promote_post_insights_entry_universe,ig_android_camera_async_setup_lowend_focus,ig_android_direct_text_shim_viewholder,ig_android_ad_iab_qpl_kill_switch_universe,ig_android_live_subscribe_user_level_universe,ig_android_vc_sounds_universe,ig_android_video_call_finish_universe,direct_unread_reminder_qe,ig_android_direct_mqtt_send,ig_android_prefetch_logic_infra,ig_biz_growth_insights_universe,ig_android_self_story_button_non_fbc_accounts,ig_android_self_profile_suggest_business_gating,ig_android_migrate_gifs_to_ig_endpoint,ig_feed_video_autoplay_stop_threshold,ig_android_explore_discover_people_entry_point_universe,ig_android_live_webrtc_livewith_params,ig_android_payments_growth_promote_payments_without_payments,ig_camera_android_effect_metadata_cache_refresh_universe,ig_feed_experience,ig_android_direct_activator_cards,ig_android_vc_codec_settings,ig_promote_prefill_destination_universe,ig_android_appstate_logger,ig_android_video_cached_bandwidth_estimate,ig_promote_insights_video_views_universe,ig_android_use_action_sheet_for_media_overflow,ig_android_profile_unified_creation_universe,ig_android_discover_interests_universe,ig_prefetch_scheduler_backtest,ig_android_camera_gallery_upload_we_universe,ig_android_dismiss_recent_searches,ig_android_feed_camera_size_setter,ig_payment_checkout_cvv,ig_android_fb_link_ui_polish_universe,ig_android_qr_code_scanner,ig_android_shopping_lightbox,ig_camera_android_async_effect_api_parsing_universe,ig_android_bandwidth_timed_estimator,ig_iab_tti_holdout_universe,ig_android_profile_ppr,ig_android_camera_gyro_universe,ig_android_igtv_ssim_report,ig_android_stories_gallery_sticker_universe,ig_android_promote_migration_gamma_universe,ig_android_business_remove_unowned_fb_pages,ig_android_spark_arengine_igl_activations,ig_search_client_cache_overriding_universe,ig_promote_enter_error_screens_universe,ig_stories_allow_camera_actions_while_recording,ig_android_analytics_mark_events_as_offscreen,ig_shopping_checkout_mvp_experiment,ig_android_video_fit_scale_type_igtv,ig_android_wellbeing_support_frx_friction_process_education,ig_android_direct_pending_media,ig_android_scroll_main_feed,instagram_pcp_activity_feed_following_tab_universe,instagram_pcp_bloks_qp_universe,ig_android_igtv_player_follow_button,ig_android_arengine_remote_scripting_universe,ig_android_intialization_chunk_410,ig_android_camera_multi_capture_max_recording_segments,ig_android_recognition_tracking_thread_prority_universe,ig_android_checkout_awareness_universe,ig_android_stories_music_sticker_position,ig_android_hec_promote_universe,ig_android_optic_photo_cropping_fixes,ig_camera_android_gallery_search_universe,ig_android_vc_cowatch_config_universe,ig_android_nametag_save_experiment_universe,ig_android_direct_continuous_capture,ig_android_comments_direct_reply_to_author,ig_android_fs_new_gallery,ig_android_media_remodel,ig_camera_android_share_effect_link_universe,ig_android_ads_rendering_logging,ig_android_remove_follow_all_fb_list,ig_android_vc_webrtc_params,ig_android_specific_story_sharing,ig_location_tagging_product_universe,ig_android_image_exif_metadata_ar_effect_id_universe,ig_android_optic_new_architecture,ig_android_on_notification_cleared_async_universe,ig_new_eof_demarcator_universe";
	const std::string Constants::supported_capabilities_new = "[{\"name\":\"SUPPORTED_SDK_VERSIONS\",\"value\":\"45.0,46.0,47.0,48.0,49.0,50.0,51.0,52.0,53.0,54.0,55.0,56.0,57.0,58.0,59.0,60.0,61.0,62.0,63.0,64.0,65.0,66.0,67.0,68.0,69.0,70.0,71.0,72.0,73.0,74.0,75.0,76.0,77.0,78.0,79.0,80.0,81.0,82.0,83.0\"},{\"name\":\"FACE_TRACKER_VERSION\",\"value\":\"14\"},{\"name\":\"segmentation\",\"value\":\"segmentation_enabled\"},{\"name\":\"COMPRESSION\",\"value\":\"ETC2_COMPRESSION\"},{\"name\":\"world_tracker\",\"value\":\"world_tracker_enabled\"}]";
	const std::string Constants::surfaces_to_queries = "{\\\"4715\\\":\\\"Query+QuickPromotionSurfaceQuery:+Viewer+{viewer()+{eligible_promotions.trigger_context_v2(<trigger_context_v2>).ig_parameters(<ig_parameters>).trigger_name(<trigger_name>).surface_nux_id(<surface>).external_gating_permitted_qps(<external_gating_permitted_qps>).supports_client_filters(true).include_holdouts(true)+{edges+{client_ttl_seconds,log_eligibility_waterfall,is_holdout,priority,time_range+{start,end},node+{id,promotion_id,logging_data,max_impressions,triggers,contextual_filters+{clause_type,filters+{filter_type,unknown_action,value+{name,required,bool_value,int_value,string_value},extra_datas+{name,required,bool_value,int_value,string_value}},clauses+{clause_type,filters+{filter_type,unknown_action,value+{name,required,bool_value,int_value,string_value},extra_datas+{name,required,bool_value,int_value,string_value}},clauses+{clause_type,filters+{filter_type,unknown_action,value+{name,required,bool_value,int_value,string_value},extra_datas+{name,required,bool_value,int_value,string_value}},clauses+{clause_type,filters+{filter_type,unknown_action,value+{name,required,bool_value,int_value,string_value},extra_datas+{name,required,bool_value,int_value,string_value}}}}}},is_uncancelable,template+{name,parameters+{name,required,bool_value,string_value,color_value,}},creatives+{title+{text},content+{text},footer+{text},social_context+{text},social_context_images,primary_action{title+{text},url,limit,dismiss_promotion},secondary_action{title+{text},url,limit,dismiss_promotion},dismiss_action{title+{text},url,limit,dismiss_promotion},image.scale(<scale>)+{uri,width,height}}}}}}}\\\",\\\"5858\\\":\\\"Query+QuickPromotionSurfaceQuery:+Viewer+{viewer()+{eligible_promotions.trigger_context_v2(<trigger_context_v2>).ig_parameters(<ig_parameters>).trigger_name(<trigger_name>).surface_nux_id(<surface>).external_gating_permitted_qps(<external_gating_permitted_qps>).supports_client_filters(true).include_holdouts(true)+{edges+{client_ttl_seconds,log_eligibility_waterfall,is_holdout,priority,time_range+{start,end},node+{id,promotion_id,logging_data,max_impressions,triggers,contextual_filters+{clause_type,filters+{filter_type,unknown_action,value+{name,required,bool_value,int_value,string_value},extra_datas+{name,required,bool_value,int_value,string_value}},clauses+{clause_type,filters+{filter_type,unknown_action,value+{name,required,bool_value,int_value,string_value},extra_datas+{name,required,bool_value,int_value,string_value}},clauses+{clause_type,filters+{filter_type,unknown_action,value+{name,required,bool_value,int_value,string_value},extra_datas+{name,required,bool_value,int_value,string_value}},clauses+{clause_type,filters+{filter_type,unknown_action,value+{name,required,bool_value,int_value,string_value},extra_datas+{name,required,bool_value,int_value,string_value}}}}}},is_uncancelable,template+{name,parameters+{name,required,bool_value,string_value,color_value,}},creatives+{title+{text},content+{text},footer+{text},social_context+{text},social_context_images,primary_action{title+{text},url,limit,dismiss_promotion},secondary_action{title+{text},url,limit,dismiss_promotion},dismiss_action{title+{text},url,limit,dismiss_promotion},image.scale(<scale>)+{uri,width,height}}}}}}}\\\",\\\"5734\\\":\\\"Query+QuickPromotionSurfaceQuery:+Viewer+{viewer()+{eligible_promotions.trigger_context_v2(<trigger_context_v2>).ig_parameters(<ig_parameters>).trigger_name(<trigger_name>).surface_nux_id(<surface>).external_gating_permitted_qps(<external_gating_permitted_qps>).supports_client_filters(true).include_holdouts(true)+{edges+{client_ttl_seconds,log_eligibility_waterfall,is_holdout,priority,time_range+{start,end},node+{id,promotion_id,logging_data,max_impressions,triggers,contextual_filters+{clause_type,filters+{filter_type,unknown_action,value+{name,required,bool_value,int_value,string_value},extra_datas+{name,required,bool_value,int_value,string_value}},clauses+{clause_type,filters+{filter_type,unknown_action,value+{name,required,bool_value,int_value,string_value},extra_datas+{name,required,bool_value,int_value,string_value}},clauses+{clause_type,filters+{filter_type,unknown_action,value+{name,required,bool_value,int_value,string_value},extra_datas+{name,required,bool_value,int_value,string_value}},clauses+{clause_type,filters+{filter_type,unknown_action,value+{name,required,bool_value,int_value,string_value},extra_datas+{name,required,bool_value,int_value,string_value}}}}}},is_uncancelable,template+{name,parameters+{name,required,bool_value,string_value,color_value,}},creatives+{title+{text},content+{text},footer+{text},social_context+{text},social_context_images,primary_action{title+{text},url,limit,dismiss_promotion},secondary_action{title+{text},url,limit,dismiss_promotion},dismiss_action{title+{text},url,limit,dismiss_promotion},image.scale(<scale>)+{uri,width,height}}}}}}}\\\"}";

	const std::string Constants::folder = "./files/ig/";

	const std::string Constants::file_log = folder + "log.dat";
}
