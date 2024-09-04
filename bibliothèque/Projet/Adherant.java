import java.util.ArrayList;
public class Adherant {
    private final int Max=5;
    private String nom;
    private String prenom;
    private Statut statut;
    private boolean emprunterOrdi;
    private ArrayList <OrdinateurPortable> dispo;
    private int nbEmprunts=0;
    private ArrayList <Livre> emprunts;
    private boolean dispoLivre;
    public Adherant(String nom,String prenom,Statut statut){
        this.nom=nom;
        this.prenom=prenom;
        this.statut=statut;
    }
    public void emprunterOrdi(OrdinateurPortable a){
        if(emprunterOrdi=false){
            dispo.add(a);
            emprunterOrdi=true;
        }
        System.out.println("voous avez déja un ordi");
    }
    public void emprunterLivre(Livre livre){
        if(nbEmprunts<5){
        for(int i=0; i<emprunts.size(); i++){
                if(livre==emprunts.get(i)){
                    dispoLivre=true;
                }
                if(dispoLivre==false){
                    emprunts.add(livre);
                    nbEmprunts++;
                }
        }
        System.out.println("vous avez déjà 5 livres");
    }
    }
    public void rendreOrdi(OrdinateurPortable ordi) {
            if (emprunterOrdi=true) {
                dispo.remove(ordi);
                emprunterOrdi = false;
                System.out.println("L'ordinateur portable a été rendu avec succès.");
            } else {
                System.out.println("Vous n'avez pas emprunté d'ordinateur portable.");
            }
        }
        

    public void rendreLivre(Livre livre) {
        boolean rendu = false;
        for (int i = 0; i < emprunts.size(); i++) {
            if (emprunts.get(i) == livre) {
                emprunts.remove(i);
                nbEmprunts--;
                System.out.println("Le livre a été rendu avec succès.");
                rendu = true;
                break;
            }
        }
        if (!rendu) {
            System.out.println("Vous n'avez pas emprunté ce livre.");
        }
    }
}
