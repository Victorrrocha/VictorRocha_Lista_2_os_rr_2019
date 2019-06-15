#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/list.h>
#include<linux/slab.h>

// by: Franciso Nascimento and Victor Barbosa

/*
	Código adaptador de: http://tuxthink.blogspot.com/2014/02/creating-linked-list-in-liinux-kernel.html
	Data: 14-06-2019 17:00
*/

/*
	Simulando uma lista de tarefas:
		Limpeza de uma casa.

		- Pegando materias de limpeza.
		- Varrer a casa.
		- passar pano no chão.
		- Jogar o lixo pra fora.
		- Guardar materiais de limpeza.
		- Descançar.
*/

// criando struct das tarefas
struct tarefa {
	struct list_head test_list;
	char conteudo[30];
};

// Inicialização do modulo
static int __init create_list_init(void) 
{
	// Criando ponteitos das variaveis das tarefas e a lista de tarefas
	struct tarefa *tarefa01,*tarefa02,*tarefa03,*tarefa04,*tarefa05,*entry;
	struct list_head minhasTarefas;
	struct list_head *ptr;

	// Alocando espaços para os ponteiros das variaveis de tarefas
	tarefa01=kmalloc(sizeof(struct tarefa *),GFP_KERNEL);
	tarefa02=kmalloc(sizeof(struct tarefa *),GFP_KERNEL);
	tarefa03=kmalloc(sizeof(struct tarefa *),GFP_KERNEL);
	tarefa04=kmalloc(sizeof(struct tarefa *),GFP_KERNEL);
	tarefa05=kmalloc(sizeof(struct tarefa *),GFP_KERNEL);

	// Adicionando Tarefaz às variaveis
	strcpy(tarefa01->conteudo,"Pegando materiais de limpeza!");
	strcpy(tarefa02->conteudo,"Varrer a casa.");
	strcpy(tarefa03->conteudo,"Passar pano no chão.");
	strcpy(tarefa04->conteudo,"Jogar lixo para fora.");
	strcpy(tarefa05->conteudo,"Guardar materiais de limpeza.");

	// Iniciando a lista "minhasTarefas" e adicionando as tarefas criadas na lista
	INIT_LIST_HEAD(&minhasTarefas);
	list_add(&tarefa01->test_list,&minhasTarefas);
	list_add(&tarefa02->test_list,&minhasTarefas);
	list_add(&tarefa03->test_list,&minhasTarefas);
	list_add(&tarefa04->test_list,&minhasTarefas);
	list_add(&tarefa05->test_list,&minhasTarefas);

	/*
	// Imprimir a lista criada
	// A função "list_for_each" percorre a lista "minhasTarefas" 
	list_for_each(ptr,&minhasTarefas)
	{
		// Ao usar a função "list_entry" nao se pode acessar o conteúdo
		// de em "ptr", entao esta armazendo em "entry" onde pode ter
		// acesso ao conteudo.
		entry=list_entry(ptr,struct tarefa,test_list);
		// Imprimindo "entry", onde contem a cada momento o conteudo(tarefa) da lista
		printk(KERN_INFO "\n Tarefa: %s  \n ", entry->conteudo);

	}*/

	list_for_each(ptr,&minhasTarefas)
	{
		entry=list_entry(ptr,struct tarefa,test_list);


		printk(KERN_INFO "\n Tarefa: %d  \n ", entry->conteudo);

	}

	return 0;

}

// Mensagem de finalização do modulo
static void __exit create_list_exit(void) {
	printk(KERN_INFO "Goodbye! Indo descançar um pouco... Mereço! \n");
}

// Inicializador e Finalizador do modulo
module_init(create_list_init);
module_exit(create_list_exit);

MODULE_LICENSE("GPL");