#include<stdio.h>
#include<lightdm.h>
#include<gtk/gtk.h>
static void session_details(LightDMSession *session){

		printf("\tSession Name : %s\n",lightdm_session_get_name(session));
		printf("\tSession Type : %s\n",lightdm_session_get_session_type(session));
		printf("\tSession Key : %s\n",lightdm_session_get_key(session));
		printf("\tSession description : %s\n",lightdm_session_get_comment(session));
}
static void get_session(){
	GList *session_list,*list = lightdm_get_sessions();
  	for (session_list = list; session_list; session_list = session_list->next){
        	printf("\nSession Details :-\n");
		session_details(session_list->data);

	}
}
static void get_hostname(){
	printf("\nHostName :-\t%s\n",lightdm_get_hostname());
}

static void get_power_options(){
	printf("\nPower Options :-\n");
	if(!lightdm_get_can_suspend()){
		printf("\tSleep :- Not Available\n");
	}else{
		printf("\tSleep :- Available\n");
	}if(!lightdm_get_can_hibernate()){
		printf("\tHibernate :- Not Available\n");
	}else{
		printf("\tHibernate :- Available\n");
	}if(!lightdm_get_can_restart()){
		printf("\tRestart :- Not Available\n");
	}else{
		printf("\tRestart :- Available\n");
	}if(!lightdm_get_can_shutdown()){
		printf("\tShutdown :- Not Available\n");
	}else{
		printf("\tShutdown :- Available\n");
	}
}

static void get_user_detail(LightDMUser *user){
	printf("\tUserName :- %s\n",lightdm_user_get_name(user));
	printf("\tReal Name :- %s\n",lightdm_user_get_real_name(user));
	printf("\tDisplay Name :- %s\n",lightdm_user_get_display_name(user));
	printf("\tUser Home Directory :- %s\n",lightdm_user_get_home_directory(user));
	printf("\tUser Image URL :- %s\n",lightdm_user_get_image(user));
	printf("\tUser Background File URL :- %s\n",lightdm_user_get_background(user));
	printf("\tUser Language :- %s\n",lightdm_user_get_language(user));
	printf("\tUser keyboard Layout :- %s\n",lightdm_user_get_layouts(user));
	printf("\tUser Session :- %s\n",lightdm_user_get_session(user));
	printf("\tUser Is Logged In :- %s\n",(lightdm_user_get_logged_in(user))?"Logged In":"Not Logged In");
	printf("\tUser Messages :- %s\n",(lightdm_user_get_has_messages(user))?"Have Message":"No Message");

	printf("\tUser ID :- %d\n",lightdm_user_get_uid(user));
}

static void get_user_list(){
	LightDMUserList *user_list = lightdm_user_list_get_instance();
	printf("User List Lenght :- %d\n",lightdm_user_list_get_length(user_list));
	GList *list ,*lists= lightdm_user_list_get_users(user_list);
	for (list = lists; list; list= list->next){
		
		printf("\nUser Detail :\n");
        	get_user_detail(list->data);
	}

}

static void keyboard_layout_detail(LightDMLayout *layout){
	printf("\tKeyboard Layout Name :- %s\n",lightdm_layout_get_name(layout));
	printf("\tKeyboard Layout Short Description :- %s\n",lightdm_layout_get_short_description(layout));
	printf("\tKeyboard Layout Description :- %s\n",lightdm_layout_get_description(layout));	
}

static void get_keyboard_layout(){
	GList *key_list,*lists = lightdm_get_layouts();
	
	printf("Current Keyboard Layout :- \n");
	keyboard_layout_detail(lightdm_get_layout());
	for (key_list = lists;key_list; key_list= key_list->next){
		
		printf("\nAvailable Keyboard Layout Detail :-\n");
        	keyboard_layout_detail(key_list->data);
	}

}

static void get_language_detail(LightDMLanguage *language){	
	printf("\tLanguage Name :- %s\n",lightdm_language_get_name(language));
	printf("\tLanguage Code :- %s\n",lightdm_language_get_code(language));
	printf("\tLanguage Territory :- %s\n",lightdm_language_get_territory(language));
	printf("\tLanguage Name :- %s\n",lightdm_language_get_name(language));
	
}

static void get_language(){
	GList *lang_list,*lists = lightdm_get_languages();
	printf("Current System language :- \n");	
	(lightdm_get_language())? get_language_detail(lightdm_get_language()) :printf("No Default language pack \n");
	for (lang_list = lists;lang_list; lang_list= lang_list->next){
		
		printf("\nAvailable System languages Detail :-\n");
        	get_language_detail(lang_list->data);
	}

}

int main(int argc,char **argv){
	

	printf("\n\n\t\tHostName\n\n");
	get_hostname();
	printf("\n\n\t\tSession\n\n");
	get_session();
	printf("\n\n\t\tPower Options\n\n");
	get_power_options();
	printf("\n\n\t\tUser List\n\n");
	get_user_list();
	printf("\n\n\t\tKeyboard Layout\n\n");
	get_keyboard_layout();
	printf("\n\n\t\tLanguages\n\n");
	get_language();
	return 0;
}
