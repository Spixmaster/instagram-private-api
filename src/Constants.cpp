#include "ig/Constants.h"
#include <string>
#include <iostream>

namespace ig
{
	const std::string Constants::version = "0.18";
	const std::string Constants::release = "29.Dec.2019";

	const std::string Constants::ig_url = "https://i.instagram.com/api/v1/";
	const std::string Constants::ig_sig_key_version = "4";
	const std::string Constants::ig_sig_key = "5f3e50f435583c9ae626302a71f7340044087a7e2c60adacfc254205a993e305";
	const std::string Constants::launcher_configs =
			"ig_android_felix_release_players,ig_user_mismatch_soft_error,"
		    "ig_android_os_version_blocking_config,"
		    "ig_android_carrier_signals_killswitch,fizz_ig_android,"
		    "ig_mi_block_expired_events,ig_android_killswitch_perm_direct_ssim,"
		    "ig_fbns_blocked";
	const std::string Constants::login_experiments =
			"ig_android_fci_onboarding_friend_search,ig_android_device_detection_info_"
		    "upload,ig_android_autosubmit_password_recovery_universe,ig_growth_android"
		    "_profile_pic_prefill_with_fb_pic_2,ig_account_identity_logged_out_signals"
		    "_global_holdout_universe,ig_android_background_voice_phone_confirmation_p"
		    "refilled_phone_number_only,ig_android_login_identifier_fuzzy_match,ig_and"
		    "roid_one_tap_aymh_redesign_universe,ig_android_keyboard_detector_fix,ig_a"
		    "ndroid_suma_landing_page,ig_android_direct_main_tab_universe,ig_android_a"
		    "ymh_signal_collecting_kill_switch,ig_android_login_forgot_password_univer"
		    "se,ig_android_smartlock_hints_universe,ig_android_smart_prefill_killswitc"
		    "h,ig_android_account_switch_infra_universe,ig_android_multi_tap_login_new"
		    ",ig_android_email_one_tap_auto_login_during_reg,ig_android_category_searc"
		    "h_in_sign_up,ig_android_report_nux_completed_device,ig_android_reg_login_"
		    "profile_photo_universe,ig_android_caption_typeahead_fix_on_o_universe,ig_"
		    "android_nux_add_email_device,ig_android_ci_opt_in_placement,ig_android_re"
		    "member_password_at_login,ig_type_ahead_recover_account,ig_android_analyti"
		    "cs_accessibility_event,ig_sem_resurrection_logging,ig_android_abandoned_r"
		    "eg_flow,ig_android_editable_username_in_reg,ig_android_account_recovery_a"
		    "uto_login,ig_android_sim_info_upload,ig_android_skip_signup_from_one_tap_"
		    "if_no_fb_sso,ig_android_hide_fb_flow_in_add_account_flow,ig_android_mobil"
		    "e_http_flow_device_universe,ig_account_recovery_via_whatsapp_universe,ig_"
		    "android_hide_fb_button_when_not_installed_universe,ig_prioritize_user_inp"
		    "ut_on_switch_to_signup,ig_android_gmail_oauth_in_reg,ig_android_login_saf"
		    "etynet,ig_android_gmail_autocomplete_account_over_one_tap,ig_android_back"
		    "ground_voice_phone_confirmation,ig_android_phone_auto_login_during_reg,ig"
		    "_android_hide_typeahead_for_logged_users,ig_android_hindi,ig_android_reg_"
		    "modularization_universe,ig_android_bottom_sheet,ig_android_snack_bar_hidi"
		    "ng,ig_android_one_tap_fallback_auto_login,ig_android_device_verification_"
		    "separate_endpoint,ig_account_recovery_with_code_android_universe,ig_andro"
		    "id_onboarding_skip_fb_connect,ig_android_phone_reg_redesign_universe,ig_a"
		    "ndroid_universe_noticiation_channels,ig_android_media_cache_cleared_unive"
		    "rse,ig_android_account_linking_universe,ig_android_hsite_prefill_new_carr"
		    "ier,ig_android_retry_create_account_universe,ig_android_family_apps_user_"
		    "values_provider_universe,ig_android_reg_nux_headers_cleanup_universe,ig_a"
		    "ndroid_dialog_email_reg_error_universe,ig_android_ci_fb_reg,ig_android_de"
		    "vice_info_foreground_reporting,ig_fb_invite_entry_points,ig_android_devic"
		    "e_verification_fb_signup,ig_android_suma_biz_account,ig_android_onetaplog"
		    "in_optimization,ig_video_debug_overlay,ig_android_ask_for_permissions_on_"
		    "reg,ig_android_display_full_country_name_in_reg_universe,ig_android_exopl"
		    "ayer_settings,ig_android_persistent_duplicate_notif_checker,ig_android_se"
		    "curity_intent_switchoff,ig_android_background_voice_confirmation_block_ar"
		    "gentinian_numbers,ig_android_do_not_show_back_button_in_nux_user_list,ig_"
		    "android_passwordless_auth,ig_android_direct_main_tab_account_switch,ig_an"
		    "droid_modularized_dynamic_nux_universe,ig_android_icon_perf2,ig_android_e"
		    "mail_suggestions_universe,ig_android_fb_account_linking_sampling_freq_uni"
		    "verse,ig_android_prefill_full_name_from_fb,ig_android_access_flow_prefill";

	const std::string Constants::files_folder = "files/ig/";
}
