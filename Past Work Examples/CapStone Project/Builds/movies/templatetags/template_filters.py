from django import template
from django.conf import settings                                                                                                         
                                                                                                            

register = template.Library()

@register.filter
def keyvalue(dict, key):    
    return dict[key]

@register.filter
def addstr(arg1, arg2):
    """concatenate arg1 & arg2"""
    return str(arg1) + str(arg2)

@register.filter
def listelem(list,index):
	return list[index]

@register.simple_tag(name='cache_bust')                                                                                                  
def cache_bust():                                                                                                                        

    if settings.DEBUG:                                                                                                                   
        version = uuid.uuid1()                                                                                                           
    else:                                                                                                                                
        version = os.environ.get('PROJECT_VERSION')                                                                                       
        if version is None:                                                                                                              
            version = '1'                                                                                                                

    return '__v__={version}'.format(version=version)