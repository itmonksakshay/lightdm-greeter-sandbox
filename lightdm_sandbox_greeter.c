#include<stdio.h>
#include<lightdm.h>
#include<gtk/gtk.h>
#include<stdlib.h>
#include<string.h>

int global_counter;

typedef struct data_struct {
	gchar *data_header;
	const gchar *data_value;

}output_data;

typedef struct info_struct {
	const	gchar *object_name;
	output_data *object_value;

}object_info;
output_data *session_details(LightDMSession *session){
		
		output_data *value = (output_data*)malloc(3*sizeof(output_data));
		(value+0)->data_header = "Session Type";
		(value+0)->data_value = lightdm_session_get_session_type(session);
		(value+1)->data_header = "Session Key";
		(value+1)->data_value = lightdm_session_get_key(session);
		(value+2)->data_header = "session description";
		(value+2)->data_value = lightdm_session_get_comment(session);

		return value;
}
object_info *get_session(){
	GList *session_list,*list = lightdm_get_sessions();
	gint lt =0;
	object_info *value = (object_info*)malloc(100*sizeof(object_info));
  	for (session_list = list; session_list; session_list = session_list->next){
        	(value+lt)->object_name	= lightdm_session_get_name(session_list->data);
		output_data *data = session_details(session_list->data);
		(value+lt)->object_value = data;
		lt++;
	}
	global_counter=lt;
	return value;
}


output_data  *get_hostname(){
	output_data *value = (output_data*)malloc(1*sizeof(output_data));
	value->data_header = "Hostname";
	value->data_value = lightdm_get_hostname();
	return value;
}

output_data *get_power_options(){
	
	output_data *value = (output_data*)malloc(4*sizeof(output_data));

		(value+0)->data_header = "Sleep Option";
		if(!lightdm_get_can_suspend()){
			(value+0)->data_value = "Not Available";
		}else{	
			(value+0)->data_value = " Available";
		}
		(value+1)->data_header = "Hibernate Option";
		if(!lightdm_get_can_hibernate()){
			(value+1)->data_value = "Not Available";
		}else{
			(value+1)->data_value = " Available";
		}
		(value+2)->data_header = "Restart Option";
		if(!lightdm_get_can_restart()){
			(value+2)->data_value = "Not Available";
		}else{
			(value+2)->data_value = " Available";
		}
		(value+3)->data_header = "Shutdown Option";
		if(!lightdm_get_can_shutdown()){
			(value+3)->data_value = "Not Available";
		}else{
			(value+3)->data_value = " Available";
		}
	return value;
}

output_data *get_user_detail(LightDMUser *user){
	
	output_data *value = (output_data*)malloc(11*sizeof(output_data));
	(value+0)->data_header = "Real Name";
	(value+0)->data_value = lightdm_user_get_real_name(user);
	(value+1)->data_header = "Display Name";
	(value+1)->data_value = lightdm_user_get_display_name(user);
	(value+2)->data_header = "User Home Directory";
	(value+2)->data_value = lightdm_user_get_home_directory(user);
	(value+3)->data_header = "User Image URL";
	(value+3)->data_value = lightdm_user_get_image(user);
	(value+4)->data_header = "User Background File URL";
	(value+4)->data_value = lightdm_user_get_background(user);
	(value+5)->data_header = "User Language ";
	(value+5)->data_value = lightdm_user_get_language(user);
	(value+6)->data_header = "User keyboard Layout";
	(value+6)->data_value = (gchar *)lightdm_user_get_layouts(user);
	(value+7)->data_header = "User Session ";
	(value+7)->data_value = lightdm_user_get_session(user);
	(value+8)->data_header = "User Is Logged In ";
	(value+8)->data_value = (lightdm_user_get_logged_in(user))?"Logged In":"Not Logged In";
	(value+9)->data_header = "User Messages";
	(value+9)->data_value=(lightdm_user_get_has_messages(user))?"Have Message":"No Message";
	(value+10)->data_header = "User ID";
	
	char *buffer_data = malloc(5*sizeof(int));
	sprintf(buffer_data,"%d",lightdm_user_get_uid(user));
	(value+10)->data_value = buffer_data;
	free(buffer_data);
	return value;
}

LightDMUserList *get_user_list(){
	return lightdm_user_list_get_instance();
}

output_data *user_number(LightDMUserList *user_list){
	output_data *get_data = (output_data*)malloc(1*sizeof(output_data));
        char *buffer_data = malloc(10*sizeof(char));
	get_data->data_header ="Number Of Users";
	sprintf(buffer_data,"%d",lightdm_user_list_get_length(user_list));
	get_data->data_value = buffer_data;

	return get_data;

}

object_info *list_users(){
	LightDMUserList *user_list = get_user_list();
	global_counter = lightdm_user_list_get_length(user_list);	
	object_info *value = (object_info*)malloc(global_counter*sizeof(object_info));
	GList *list ,*lists= lightdm_user_list_get_users(user_list);
	gint lt=0;
	for (list = lists; list; list= list->next){
		(value+lt)->object_name	= lightdm_user_get_name(list->data);
		output_data *data = get_user_detail(list->data);
		(value+lt)->object_value = data;
		lt++;
	}

	return value;
}
output_data *current_keyboard_layout(){

	output_data *value = (output_data*)malloc(1*sizeof(output_data));

	value->data_header = "Default Keyboard";
	value->data_value = lightdm_layout_get_name(lightdm_get_layout());

	return value;
}
	


output_data *keyboard_layout_detail(LightDMLayout *layout){

	output_data *value = (output_data*)malloc(2*sizeof(output_data));
	
	(value+0)->data_header = "Keyboard Layout Short Description" ;
	(value+0)->data_value = lightdm_layout_get_short_description(layout);
	(value+1)->data_header ="Keyboard Layout Description";
	(value+1)->data_value = lightdm_layout_get_description(layout);
	
	return value;	
}

object_info *get_keyboard_layout(){
	GList *key_list,*lists = lightdm_get_layouts();
	

	object_info *value = (object_info*)malloc(1000*sizeof(object_info));
	gint lt =0;
	for (key_list = lists;key_list; key_list= key_list->next){
	
		(value+lt)->object_name =lightdm_layout_get_name(key_list->data);
        	(value+lt)->object_value= keyboard_layout_detail(key_list->data); 
		lt++;
	}
	global_counter = lt;
	return value;

}

output_data *get_language_detail(LightDMLanguage *language){

	output_data *value = (output_data*)malloc(3*sizeof(output_data));
	
	(value+0)->data_header = "Language Code";
	(value+0)->data_value = lightdm_language_get_code(language);
	(value+1)->data_header = "Language Territory";
	(value+1)->data_value = lightdm_language_get_territory(language);
	(value+2)->data_header = "Language Name";
	(value+2)->data_value = lightdm_language_get_name(language);

	return value;
	
}

output_data *default_language(){

	output_data *value = (output_data*)malloc(1*sizeof(output_data));
		value->data_header ="Default language pack";
		value->data_value = (lightdm_get_language())? lightdm_language_get_name(lightdm_get_language()) :"No Default language pack";

		return value;
}

object_info *get_language(){
	GList *lang_list,*lists = lightdm_get_languages();

	object_info *value = (object_info*)malloc(1000*sizeof(object_info));
	gint lt =0;
	for (lang_list = lists;lang_list; lang_list= lang_list->next){
		
		(value+lt)->object_name = lightdm_language_get_name(lang_list->data);
		(value+lt)->object_value = get_language_detail(lang_list->data);
		lt++;
	}
	global_counter = lt;
	return value;

}

enum{
	NAME=0,VALUE,NUM_COLS
};

GtkTreeModel *data_entry_model(){

  	GtkTreeStore *treestore;
    	GtkTreeIter toplevel,toplevelchild,child;
      	treestore = gtk_tree_store_new(NUM_COLS,G_TYPE_STRING,G_TYPE_STRING);

	//System Information

	output_data *sys_info = get_hostname();

	gtk_tree_store_append(treestore, &toplevel, NULL);
  	gtk_tree_store_set(treestore, &toplevel,NAME, "System Information",-1);
 	gtk_tree_store_append(treestore, &child, &toplevel);
  	gtk_tree_store_set(treestore, &child,NAME,(sys_info)->data_header,-1);
	gtk_tree_store_set(treestore, &child,VALUE,(sys_info)->data_value,-1);
	
	
	free(sys_info);

	//Power Options
	
	output_data *value = get_power_options();

	gtk_tree_store_append(treestore, &toplevel, NULL);
  	gtk_tree_store_set(treestore, &toplevel,NAME, "Power Options",-1);
	for(int i=0;i<4;i++){
  		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child,NAME, (value+i)->data_header,-1);
		gtk_tree_store_set(treestore, &child,VALUE,(value+i)->data_value,-1);
	}
	free(value);

	//User Details
	gtk_tree_store_append(treestore, &toplevel, NULL);
  	gtk_tree_store_set(treestore, &toplevel,NAME, "User Details",-1);

	//Number of Users
	output_data *user_info = user_number(get_user_list()); 
  	gtk_tree_store_append(treestore, &child, &toplevel);
  	gtk_tree_store_set(treestore, &child,NAME,user_info->data_header,-1);
	gtk_tree_store_set(treestore, &child,VALUE,user_info->data_value,-1);
	
	//Full Detail of Users
	
	object_info *user_value =list_users();
	output_data *user_detail;
  	for(int i=0;i<global_counter;i++){
		gtk_tree_store_append(treestore,&toplevelchild,&toplevel);
	gtk_tree_store_set(treestore, &toplevelchild,NAME,(user_value+i)->object_name,-1);
	user_detail = (user_value+i)->object_value;
		for(int j=0;j<11;j++){
			gtk_tree_store_append(treestore, &child, &toplevelchild);
		gtk_tree_store_set(treestore, &child,NAME,(user_detail+j)->data_header,-1);
		gtk_tree_store_set(treestore, &child,VALUE,(user_detail+j)->data_value,-1);
		
		}
	}
	free(user_info);
	free(user_value);
	
	gtk_tree_store_append(treestore, &toplevel, NULL);
  	gtk_tree_store_set(treestore, &toplevel,NAME, "Session Details",-1);

	object_info *session_value =get_session();
	output_data *session_detail;
  	for(int i=0;i<global_counter;i++){
		gtk_tree_store_append(treestore,&toplevelchild,&toplevel);
	gtk_tree_store_set(treestore, &toplevelchild,NAME,(session_value+i)->object_name,-1);
	session_detail = (session_value+i)->object_value;
		for(int j=0;j<3;j++){
			gtk_tree_store_append(treestore, &child, &toplevelchild);
		gtk_tree_store_set(treestore, &child,NAME,(session_detail+j)->data_header,-1);
		gtk_tree_store_set(treestore, &child,VALUE,(session_detail+j)->data_value,-1);
		
		}
	}
	free(session_value);

	//Keyboard List
	
	gtk_tree_store_append(treestore, &toplevel, NULL);
  	gtk_tree_store_set(treestore, &toplevel,NAME, "Available Keyboard Layouts",-1);

	output_data *keyboard_info = current_keyboard_layout(); 

	gtk_tree_store_append(treestore, &child, &toplevel);
  	gtk_tree_store_set(treestore, &child,NAME,keyboard_info->data_header,-1);
	gtk_tree_store_set(treestore, &child,VALUE,keyboard_info->data_value,-1);

	object_info *keyboard_value =get_keyboard_layout();
	output_data *keyboard_detail;
  	for(int i=0;i<global_counter;i++){
		gtk_tree_store_append(treestore,&toplevelchild,&toplevel);
	gtk_tree_store_set(treestore, &toplevelchild,NAME,(keyboard_value+i)->object_name,-1);
		keyboard_detail = (keyboard_value+i)->object_value;
		for(int j=0;j<2;j++){
			gtk_tree_store_append(treestore, &child, &toplevelchild);
		gtk_tree_store_set(treestore, &child,NAME,(keyboard_detail+j)->data_header,-1);
		gtk_tree_store_set(treestore, &child,VALUE,(keyboard_detail+j)->data_value,-1);
		
		}
	}
	free(keyboard_info);
	free(keyboard_value);
	
	//Available Languages
	

	gtk_tree_store_append(treestore, &toplevel, NULL);
  	gtk_tree_store_set(treestore, &toplevel,NAME, "Available Languages",-1);
	output_data *language_info = default_language();

	gtk_tree_store_append(treestore, &child, &toplevel);
  	gtk_tree_store_set(treestore, &child,NAME,language_info->data_header,-1);
	gtk_tree_store_set(treestore, &child,VALUE,language_info->data_value,-1);



	object_info *language_value =get_language();
	output_data *language_detail;
  	for(int i=0;i<global_counter;i++){
		gtk_tree_store_append(treestore,&toplevelchild,&toplevel);
	gtk_tree_store_set(treestore, &toplevelchild,NAME,(language_value+i)->object_name,-1);
		language_detail = (language_value+i)->object_value;
		for(int j=0;j<4;j++){
			gtk_tree_store_append(treestore, &child, &toplevelchild);
		gtk_tree_store_set(treestore, &child,NAME,(language_detail+j)->data_header,-1);
		gtk_tree_store_set(treestore, &child,VALUE,(language_detail+j)->data_value,-1);
		
		}
	}
	free(language_info);
	free(language_value);
	
	return GTK_TREE_MODEL(treestore);
	
}

GtkWidget *create_view_and_model(void) {
    
  GtkTreeViewColumn *Name,*Value;
  GtkCellRenderer *renderer;
  GtkWidget *view;
  GtkTreeModel *model;

  view = gtk_tree_view_new();

  Name = gtk_tree_view_column_new();
 // gtk_tree_view_column_set_title(Name, "Name Column");
  Value = gtk_tree_view_column_new();
 // gtk_tree_view_column_set_title(Value, "Value Column");
  gtk_tree_view_append_column(GTK_TREE_VIEW(view),Name);
  gtk_tree_view_append_column(GTK_TREE_VIEW(view),Value);

  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_column_pack_start(Name,renderer,TRUE);
  gtk_tree_view_column_pack_start(Value,renderer,TRUE);
  gtk_tree_view_column_add_attribute(Name, renderer,"text",NAME);
  gtk_tree_view_column_add_attribute(Value, renderer,"text",VALUE);

  model = data_entry_model();
  gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
  g_object_unref(model); 

  return view;
}


int main(int argc,char **argv){
	
	gtk_init(&argc,&argv);

	GtkWidget *window;
	GtkWidget *vbox;
      	GtkWidget *sw;
      	GtkWidget *treeview;
   
      /* create window, etc */
      	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
      	gtk_window_set_title (GTK_WINDOW (window), "Tree View");
      	g_signal_connect (window, "destroy",G_CALLBACK (gtk_widget_destroyed), &window);

      	vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 8);
      	gtk_container_set_border_width (GTK_CONTAINER (vbox), 8);
      	gtk_container_add (GTK_CONTAINER (window), vbox);

      	gtk_box_pack_start (GTK_BOX (vbox),gtk_label_new ("Lightdm-Greeter_sandbox"),FALSE,
		      FALSE, 0);

      	sw = gtk_scrolled_window_new(NULL, NULL);
      	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW (sw),GTK_SHADOW_ETCHED_IN);
      	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (sw),GTK_POLICY_AUTOMATIC,
		      GTK_POLICY_AUTOMATIC);
      	gtk_box_pack_start(GTK_BOX (vbox), sw,TRUE,TRUE, 0);

	treeview = create_view_and_model();
      	gtk_container_add(GTK_CONTAINER(sw) ,treeview);


	 gtk_widget_show_all(window);
	 gtk_main();

	return 0;
}
